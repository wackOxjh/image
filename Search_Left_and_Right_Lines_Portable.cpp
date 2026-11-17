#include "image.h"

// 基于原 Search_Left_and_Right_Lines 的可移植版本：
// - 适配 uLCDH/uLCDW（例如 120x160）
// - 去除 79/5/3 等硬编码
// - 增加坐标越界保护，避免巡线访问越界
// - 保留左右手法则巡线的核心行为

namespace {

static inline int ClampInt(int v, int lo, int hi) {
  return (v < lo) ? lo : ((v > hi) ? hi : v);
}

static inline int ScaleYFrom60(int y_old) {
  const float ratio = (float)(uLCDH - 1) / 59.0f;
  return ClampInt((int)(y_old * ratio + 0.5f), 0, uLCDH - 1);
}

static inline int ScaleXFrom80(int x_old) {
  const float ratio = (float)(uLCDW - 1) / 79.0f;
  return ClampInt((int)(x_old * ratio + 0.5f), 0, uLCDW - 1);
}

static inline bool IsBlackSafe(const uint8 image[uLCDH][uLCDW], int y, int x) {
  if (y < 0 || y >= uLCDH || x < 0 || x >= uLCDW) {
    return true;  // 越界视作黑墙，防止状态机跑飞
  }
  return image[y][x] == 0;
}

}  // namespace

void Search_Left_and_Right_Lines_Portable(
    uint8 imageInput[uLCDH][uLCDW], uint8 Row, uint8 Col, uint8 Bottonline) {
  (void)Row;
  (void)Col;

  const int kMaxIter = (uLCDH + uLCDW) * 3;     // 60x80 时约 420，接近原 400
  const int kMinGap = ClampInt(ScaleXFrom80(3), 2, 10);  // 原阈值 3 按宽度缩放
  const int kInitOffline = ScaleYFrom60(5);     // 原初值 5 按高度缩放
  const int kRightInit = uLCDW - 1;             // 原硬编码 79

  const int Left_Rule[2][8] = {
      {0, -1, 1, 0, 0, 1, -1, 0},      // 前向(上/右/下/左)
      {-1, -1, 1, -1, 1, 1, -1, 1},    // 左前
  };
  const int Right_Rule[2][8] = {
      {0, -1, 1, 0, 0, 1, -1, 0},      // 前向(上/右/下/左)
      {1, -1, 1, 1, -1, 1, -1, -1},    // 右前
  };

  const int bottom = ClampInt((int)Bottonline, 0, uLCDH - 1);
  int num = 0;

  int Left_Ysite = bottom;
  int Left_Xsite = ClampInt(ImageDeal[bottom].LeftBoundary, 0, uLCDW - 1);
  int Left_Rirection = 0;
  int Pixel_Left_Ysite = bottom;
  int Pixel_Left_Xsite = Left_Xsite;

  int Right_Ysite = bottom;
  int Right_Xsite = ClampInt(ImageDeal[bottom].RightBoundary, 0, uLCDW - 1);
  int Right_Rirection = 0;
  int Pixel_Right_Ysite = bottom;
  int Pixel_Right_Xsite = Right_Xsite;

  int Ysite = bottom;
  ImageStatus.OFFLineBoundary = (uint8)kInitOffline;

  while (1) {
    ++num;
    if (num > kMaxIter) {
      ImageStatus.OFFLineBoundary = (uint8)ClampInt(Ysite, 0, uLCDH - 1);
      break;
    }

    if (Ysite >= Pixel_Left_Ysite && Ysite >= Pixel_Right_Ysite) {
      if (Ysite < ImageStatus.OFFLineBoundary) {
        ImageStatus.OFFLineBoundary = (uint8)ClampInt(Ysite, 0, uLCDH - 1);
        break;
      } else {
        --Ysite;
      }
    }

    // 左边巡线
    if ((Pixel_Left_Ysite > Ysite) || Ysite == ImageStatus.OFFLineBoundary) {
      Pixel_Left_Ysite = Left_Ysite + Left_Rule[0][2 * Left_Rirection + 1];
      Pixel_Left_Xsite = Left_Xsite + Left_Rule[0][2 * Left_Rirection];

      if (IsBlackSafe(imageInput, Pixel_Left_Ysite, Pixel_Left_Xsite)) {
        Left_Rirection = (Left_Rirection == 3) ? 0 : (Left_Rirection + 1);
      } else {
        Pixel_Left_Ysite = Left_Ysite + Left_Rule[1][2 * Left_Rirection + 1];
        Pixel_Left_Xsite = Left_Xsite + Left_Rule[1][2 * Left_Rirection];

        if (IsBlackSafe(imageInput, Pixel_Left_Ysite, Pixel_Left_Xsite)) {
          Left_Ysite += Left_Rule[0][2 * Left_Rirection + 1];
          Left_Xsite += Left_Rule[0][2 * Left_Rirection];
        } else {
          Left_Ysite += Left_Rule[1][2 * Left_Rirection + 1];
          Left_Xsite += Left_Rule[1][2 * Left_Rirection];
          Left_Rirection = (Left_Rirection == 0) ? 3 : (Left_Rirection - 1);
        }

        Left_Ysite = ClampInt(Left_Ysite, 0, uLCDH - 1);
        Left_Xsite = ClampInt(Left_Xsite, 0, uLCDW - 1);
        if (ImageDeal[Left_Ysite].LeftBoundary_First == 0) {
          ImageDeal[Left_Ysite].LeftBoundary_First = Left_Xsite;
        }
        ImageDeal[Left_Ysite].LeftBoundary = Left_Xsite;
      }
    }

    // 右边巡线
    if ((Pixel_Right_Ysite > Ysite) || Ysite == ImageStatus.OFFLineBoundary) {
      Pixel_Right_Ysite = Right_Ysite + Right_Rule[0][2 * Right_Rirection + 1];
      Pixel_Right_Xsite = Right_Xsite + Right_Rule[0][2 * Right_Rirection];

      if (IsBlackSafe(imageInput, Pixel_Right_Ysite, Pixel_Right_Xsite)) {
        Right_Rirection = (Right_Rirection == 0) ? 3 : (Right_Rirection - 1);
      } else {
        Pixel_Right_Ysite = Right_Ysite + Right_Rule[1][2 * Right_Rirection + 1];
        Pixel_Right_Xsite = Right_Xsite + Right_Rule[1][2 * Right_Rirection];

        if (IsBlackSafe(imageInput, Pixel_Right_Ysite, Pixel_Right_Xsite)) {
          Right_Ysite += Right_Rule[0][2 * Right_Rirection + 1];
          Right_Xsite += Right_Rule[0][2 * Right_Rirection];
        } else {
          Right_Ysite += Right_Rule[1][2 * Right_Rirection + 1];
          Right_Xsite += Right_Rule[1][2 * Right_Rirection];
          Right_Rirection = (Right_Rirection == 3) ? 0 : (Right_Rirection + 1);
        }

        Right_Ysite = ClampInt(Right_Ysite, 0, uLCDH - 1);
        Right_Xsite = ClampInt(Right_Xsite, 0, uLCDW - 1);
        if (ImageDeal[Right_Ysite].RightBoundary_First == kRightInit) {
          ImageDeal[Right_Ysite].RightBoundary_First = Right_Xsite;
        }
        ImageDeal[Right_Ysite].RightBoundary = Right_Xsite;
      }
    }

    if (Pixel_Right_Xsite >= 0 && Pixel_Right_Xsite < uLCDW &&
        Pixel_Left_Xsite >= 0 && Pixel_Left_Xsite < uLCDW) {
      const int dx = Pixel_Right_Xsite - Pixel_Left_Xsite;
      const int adx = (dx >= 0) ? dx : -dx;
      if (adx < kMinGap) {
        ImageStatus.OFFLineBoundary = (uint8)ClampInt(Ysite, 0, uLCDH - 1);
        break;
      }
    }
  }
}

