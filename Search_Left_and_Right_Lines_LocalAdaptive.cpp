#include "image.h"

#include <math.h>
#include <stdint.h>

namespace {

constexpr int kMaxIter = 400;           // 主循环最大迭代次数
constexpr float kLowStd = 6.0f;         // 低对比阈值(标准差)
constexpr float kLowStd2 = kLowStd * kLowStd;  // 低对比阈值(方差)
constexpr float kNiblackK = 0.24f;      // 局部阈值系数
constexpr float kNearBand = 4.0f;       // 近阈值带宽
// 有效赛道识别行上限(包含该行)，默认只处理 0~100 行。
// 若希望更激进降负载，可改为 90。
constexpr int kTrackRoiMaxRow = 100;
constexpr int kOffLineBoundaryFloor = 5;

static inline int ClampInt(int v, int lo, int hi) {
  return (v < lo) ? lo : ((v > hi) ? hi : v);
}

static void BuildIntegralImages(const uint8 gray[uLCDH][uLCDW],
                                uint32 integral[uLCDH + 1][uLCDW + 1],
                                uint32 integral_sq[uLCDH + 1][uLCDW + 1],
                                int roi_max_row) {
  const int h = ClampInt(roi_max_row + 1, 1, uLCDH);
  for (int y = 0; y <= h; ++y) {
    integral[y][0] = 0;
    integral_sq[y][0] = 0;
  }
  for (int x = 0; x <= uLCDW; ++x) {
    integral[0][x] = 0;
    integral_sq[0][x] = 0;
  }

  for (int y = 1; y <= h; ++y) {
    uint32 row_sum = 0;
    uint32 row_sq_sum = 0;
    for (int x = 1; x <= uLCDW; ++x) {
      const uint8 p = gray[y - 1][x - 1];
      row_sum += p;
      row_sq_sum += (uint32)p * (uint32)p;
      integral[y][x] = integral[y - 1][x] + row_sum;
      integral_sq[y][x] = integral_sq[y - 1][x] + row_sq_sum;
    }
  }
}

static inline uint32 RectSumU32(const uint32 integral[uLCDH + 1][uLCDW + 1], int y0,
                                int x0, int y1, int x1) {
  const int ya = y0 + 1;
  const int xa = x0 + 1;
  const int yb = y1 + 1;
  const int xb = x1 + 1;
  return integral[yb][xb] - integral[ya - 1][xb] - integral[yb][xa - 1] +
         integral[ya - 1][xa - 1];
}

static inline uint32 RectSumU32Sq(const uint32 integral[uLCDH + 1][uLCDW + 1], int y0,
                                int x0, int y1, int x1) {
  const int ya = y0 + 1;
  const int xa = x0 + 1;
  const int yb = y1 + 1;
  const int xb = x1 + 1;
  return integral[yb][xb] - integral[ya - 1][xb] - integral[yb][xa - 1] +
         integral[ya - 1][xa - 1];
}

static inline int AdaptiveRadiusForRow(const int y) {
  // 行号越小表示越远，窗口稍大以提高鲁棒性。
  if (y < 30) return 6;   // 13x13
  if (y < 60) return 5;   // 11x11
  if (y < 90) return 4;   // 9x9
  return 3;               // 7x7
}

static bool IsBlackLocalAdaptive(
    const uint8 gray[uLCDH][uLCDW], const uint8 fallback_binary[uLCDH][uLCDW],
    const uint32 integral[uLCDH + 1][uLCDW + 1],
    const uint32 integral_sq[uLCDH + 1][uLCDW + 1], int y, int x, bool is_left,
    int roi_max_row) {
  // 本函数由 IsBlackSafe 调用，进入时 y/x 已保证在图像范围内。
  const bool fallback_black = (fallback_binary[y][x] == 0);

  const int r = AdaptiveRadiusForRow(y);
  const int y0 = ClampInt(y - r, 0, roi_max_row);
  const int y1 = ClampInt(y + r, 0, roi_max_row);
  const int x0 = ClampInt(x - r, 0, uLCDW - 1);
  const int x1 = ClampInt(x + r, 0, uLCDW - 1);

  const int count = (y1 - y0 + 1) * (x1 - x0 + 1);
  const float inv_count = 1.0f / (float)count;
  const float mean = (float)RectSumU32(integral, y0, x0, y1, x1) * inv_count;
  const float mean_sq = (float)RectSumU32Sq(integral_sq, y0, x0, y1, x1) * inv_count;
  const float var = (mean_sq > mean * mean) ? (mean_sq - mean * mean) : 0.0f;

  // 低对比区域直接回退到现有二值结果，避免局部阈值抖动。
  if (var < kLowStd2) {
    return fallback_black;
  }

  // Sauvola/Niblack风格: 阈值随局部亮度和方差变化。
  const float stddev = sqrtf(var);
  const float side_bias = is_left ? 1.5f : 1.0f;    //或2.0f : 1.0f
  const float row_bias = (y < 40) ? 1.0f : 0.0f;  // 远处稍微放宽黑判定
  const float threshold = mean - kNiblackK * stddev + side_bias + row_bias;

  // 简单梯度一致性: 仅在阈值附近时启用，减少误翻转。
  const int xl = (x > 0) ? (x - 1) : x;
  const int xr = (x + 1 < uLCDW) ? (x + 1) : x;
  const int gx = (int)gray[y][xr] - (int)gray[y][xl];
  const float pix = (float)gray[y][x];
  const bool near_threshold = (pix > (threshold - kNearBand) && pix < (threshold + kNearBand));
  const bool gradient_ok = is_left ? (gx >= -8) : (gx <= 8);

  if (near_threshold && !gradient_ok) {
    return fallback_black;
  }
  return pix < threshold;
}

static inline bool IsBlackSafe(
    const uint8 gray[uLCDH][uLCDW], const uint8 fallback_binary[uLCDH][uLCDW],
    const uint32 integral[uLCDH + 1][uLCDW + 1],
    const uint32 integral_sq[uLCDH + 1][uLCDW + 1], int y, int x, bool is_left,
    int roi_max_row) {
  if (y < 0 || y > roi_max_row || x < 0 || x >= uLCDW) {
    return true;  // 越界视作黑墙，防止爬线跑飞
  }
  return IsBlackLocalAdaptive(gray, fallback_binary, integral, integral_sq, y, x,
                              is_left, roi_max_row);
}

}  // namespace

// 局部二值化 + 左右手法则爬线版本。
// gray_input: 原始灰度图（推荐滤波后但未全局二值化）
// binary_fallback: 现有二值图（0黑1白），用于低对比区域兜底
void Search_Left_and_Right_Lines_LocalAdaptive(
    const uint8 gray_input[uLCDH][uLCDW],
    const uint8 binary_fallback[uLCDH][uLCDW], uint8 Bottonline) {
  static uint32 integral[uLCDH + 1][uLCDW + 1];  // 静态分配，避免大栈占用
  static uint32 integral_sq[uLCDH + 1][uLCDW + 1];  // 静态分配，避免大栈占用
  const int roi_max_row = ClampInt(kTrackRoiMaxRow, 0, uLCDH - 1);
  const int seed_row = ClampInt((int)Bottonline, 0, uLCDH - 1);  // 底边搜索得到的初始行
  const int start_row = ClampInt(seed_row, kOffLineBoundaryFloor, roi_max_row);
  BuildIntegralImages(gray_input, integral, integral_sq, roi_max_row);  // 仅在有效ROI内预计算积分图

  const int Left_Rule[2][8] = {  // 左手法则步进表
      {0, -1, 1, 0, 0, 1, -1, 0},  // [0]前向偏移，4个朝向(上/右/下/左)
      {-1, -1, 1, -1, 1, 1, -1, 1},  // [1]前对角偏移，4个朝向
  };
  const int Right_Rule[2][8] = {  // 右手法则步进表
      {0, -1, 1, 0, 0, 1, -1, 0},  // [0]前向偏移，4个朝向(上/右/下/左)
      {1, -1, 1, 1, -1, 1, -1, -1},  // [1]前对角偏移，4个朝向
  };

  int num = 0;  // 迭代计数器，避免死循环
  int Left_Ysite = start_row;  // 左边界当前y，从ROI内起始行出发
  int Left_Xsite = ClampInt(ImageDeal[seed_row].LeftBoundary, 0, uLCDW - 1);  // x 由底边检测结果作为种子
  int Left_Rirection = 0;  // 左边界朝向(0~3)
  int Pixel_Left_Ysite = start_row;  // 左边界候选点y
  int Pixel_Left_Xsite = Left_Xsite;  // 左边界候选点x

  int Right_Ysite = start_row;  // 右边界当前y，从ROI内起始行出发
  int Right_Xsite = ClampInt(ImageDeal[seed_row].RightBoundary, 0, uLCDW - 1);  // x 由底边检测结果作为种子
  int Right_Rirection = 0;  // 右边界朝向(0~3)
  int Pixel_Right_Ysite = start_row;  // 右边界候选点y
  int Pixel_Right_Xsite = Right_Xsite;  // 右边界候选点x

  int Ysite = start_row;  // 全局推进行号(从近到远向上推进)
  ImageStatus.OFFLineBoundary = kOffLineBoundaryFloor;  // 默认最远可视边界(兜底值)

  while (1) {  // 主循环: 同步推进左右边界
    ++num;  // 记录循环次数
    if (num > kMaxIter) {  // 安全保护: 迭代过多则强制退出
      ImageStatus.OFFLineBoundary = (uint8)ClampInt(Ysite, 0, uLCDH - 1);  // 记录当前终止行
      break;  // 结束爬线
    }

    if (Ysite >= Pixel_Left_Ysite && Ysite >= Pixel_Right_Ysite) {  // 左右候选都未超过当前推进行
      if (Ysite < ImageStatus.OFFLineBoundary) {  // 已经到达离线边界上方
        ImageStatus.OFFLineBoundary = (uint8)ClampInt(Ysite, 0, uLCDH - 1);  // 更新可视终点
        break;  // 结束爬线
      } else {  // 还没到终点
        --Ysite;  // 向上推进一行
      }
    }

    if ((Pixel_Left_Ysite > Ysite) || Ysite == ImageStatus.OFFLineBoundary) {  // 满足左边界更新时机
      Pixel_Left_Ysite = Left_Ysite + Left_Rule[0][2 * Left_Rirection + 1];  // 计算左边界前向候选y
      Pixel_Left_Xsite = Left_Xsite + Left_Rule[0][2 * Left_Rirection];  // 计算左边界前向候选x

      if (IsBlackSafe(gray_input, binary_fallback, integral, integral_sq,
                      Pixel_Left_Ysite, Pixel_Left_Xsite, true,
                      roi_max_row)) {  // 前向是黑，说明碰到边/墙
        Left_Rirection = (Left_Rirection == 3) ? 0 : Left_Rirection + 1;  // 顺时针转向(左手法则)
      } else {  // 前向不是黑，可进一步检查前对角
        Pixel_Left_Ysite = Left_Ysite + Left_Rule[1][2 * Left_Rirection + 1];  // 计算左边界前对角候选y
        Pixel_Left_Xsite = Left_Xsite + Left_Rule[1][2 * Left_Rirection];  // 计算左边界前对角候选x

        if (IsBlackSafe(gray_input, binary_fallback, integral, integral_sq,
                        Pixel_Left_Ysite, Pixel_Left_Xsite, true,
                        roi_max_row)) {  // 前对角是黑
          Left_Ysite += Left_Rule[0][2 * Left_Rirection + 1];  // 沿前向移动一步
          Left_Xsite += Left_Rule[0][2 * Left_Rirection];  // 更新左边界x
          if (Left_Ysite >= 0 && Left_Ysite < uLCDH) {  // 行号有效才写回
            if (ImageDeal[Left_Ysite].LeftBoundary_First == 0) {  // 该行还未记录首个左边界
              ImageDeal[Left_Ysite].LeftBoundary_First = Left_Xsite;  // 记录首个左边界
            }
            ImageDeal[Left_Ysite].LeftBoundary = Left_Xsite;  // 同步记录当前左边界
          }
        } else {  // 前向和前对角都不是黑，按规则走对角并转向
          Left_Ysite += Left_Rule[1][2 * Left_Rirection + 1];  // 沿前对角移动一步
          Left_Xsite += Left_Rule[1][2 * Left_Rirection];  // 更新左边界x
          if (Left_Ysite >= 0 && Left_Ysite < uLCDH) {  // 行号有效才写回
            if (ImageDeal[Left_Ysite].LeftBoundary_First == 0) {  // 该行还未记录首个左边界
              ImageDeal[Left_Ysite].LeftBoundary_First = Left_Xsite;  // 记录首个左边界
            }
            ImageDeal[Left_Ysite].LeftBoundary = Left_Xsite;  // 记录当前左边界
          }
          Left_Rirection = (Left_Rirection == 0) ? 3 : Left_Rirection - 1;  // 逆时针转向
        }
      }
    }

    if ((Pixel_Right_Ysite > Ysite) || Ysite == ImageStatus.OFFLineBoundary) {  // 满足右边界更新时机
      Pixel_Right_Ysite = Right_Ysite + Right_Rule[0][2 * Right_Rirection + 1];  // 计算右边界前向候选y
      Pixel_Right_Xsite = Right_Xsite + Right_Rule[0][2 * Right_Rirection];  // 计算右边界前向候选x

      if (IsBlackSafe(gray_input, binary_fallback, integral, integral_sq,
                      Pixel_Right_Ysite, Pixel_Right_Xsite, false,
                      roi_max_row)) {  // 前向是黑，说明碰到边/墙
        Right_Rirection = (Right_Rirection == 0) ? 3 : Right_Rirection - 1;  // 逆时针转向(右手法则)
      } else {  // 前向不是黑，可进一步检查前对角
        Pixel_Right_Ysite = Right_Ysite + Right_Rule[1][2 * Right_Rirection + 1];  // 计算右边界前对角候选y
        Pixel_Right_Xsite = Right_Xsite + Right_Rule[1][2 * Right_Rirection];  // 计算右边界前对角候选x

        if (IsBlackSafe(gray_input, binary_fallback, integral, integral_sq,
                        Pixel_Right_Ysite, Pixel_Right_Xsite, false,
                        roi_max_row)) {  // 前对角是黑
          Right_Ysite += Right_Rule[0][2 * Right_Rirection + 1];  // 沿前向移动一步
          Right_Xsite += Right_Rule[0][2 * Right_Rirection];  // 更新右边界x
          if (Right_Ysite >= 0 && Right_Ysite < uLCDH) {  // 行号有效才写回
            if (ImageDeal[Right_Ysite].RightBoundary_First == (uLCDW - 1)) {  // 该行还未记录首个右边界(默认最右列)
              ImageDeal[Right_Ysite].RightBoundary_First = Right_Xsite;  // 记录首个右边界
            }
            ImageDeal[Right_Ysite].RightBoundary = Right_Xsite;  // 记录当前右边界
          }
        } else {  // 前向和前对角都不是黑，按规则走对角并转向
          Right_Ysite += Right_Rule[1][2 * Right_Rirection + 1];  // 沿前对角移动一步
          Right_Xsite += Right_Rule[1][2 * Right_Rirection];  // 更新右边界x
          if (Right_Ysite >= 0 && Right_Ysite < uLCDH) {  // 行号有效才写回
            if (ImageDeal[Right_Ysite].RightBoundary_First == (uLCDW - 1)) {  // 该行还未记录首个右边界
              ImageDeal[Right_Ysite].RightBoundary_First = Right_Xsite;  // 记录首个右边界
            }
            ImageDeal[Right_Ysite].RightBoundary = Right_Xsite;  // 记录当前右边界
          }
          Right_Rirection = (Right_Rirection == 3) ? 0 : Right_Rirection + 1;  // 顺时针转向
        }
      }
    }

    if (abs(Pixel_Right_Xsite - Pixel_Left_Xsite) < 3) {  // 左右边界过近，认为已到可用上限
      ImageStatus.OFFLineBoundary = (uint8)ClampInt(Ysite, 0, uLCDH - 1);  // 更新离线边界
      break;  // 结束爬线
    }
  }
}

