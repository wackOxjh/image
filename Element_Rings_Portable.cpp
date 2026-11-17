#include "image.h"

#include <math.h>

// 可移植圆环检测/处理模块
// 设计目标:
// 1) 从旧参数(80x60坐标系)按比例映射到当前分辨率(默认160x120)。
// 2) 减少硬编码常量，增强不同摄像头分辨率下的复用性。
// 3) 保留原先状态机语义(1~9)和 Left/RightCirque 判定流程。

namespace {

enum RingSide { kLeft = 0, kRight = 1 };

// 环岛模块只处理画面上方有效区域，默认 100 行（可改成 90）。
// 这样可避免扫描底部无用行，降低算力开销。
#ifndef RING_PROCESS_HEIGHT
#define RING_PROCESS_HEIGHT 100
#endif

struct RingParams {
  int offline_max_y;
  int straight_left_s_y;
  int straight_right_s_y;
  int straight_e_y;
  int precheck_y_start;
  int precheck_y_end;

  int detect_y_top;
  int detect_y_bottom;
  int jump_delta_x;
  int shape_gap_y;
  int shape_mid_y;
  int shape_near_y;
  int p2_gap_min_y;

  int center_apply_y_bottom;
  int state_num_scan_y_start;
  int state_num_scan_y_end;
  int state_w_seq_3;
  int state_w_seq_2;
  int state_offline_left_y;
  int state_offline_right_y;
  int state_finish_scan_top;
  int state_finish_scan_bottom;
};

static inline int ClampInt(int v, int lo, int hi) {
  return (v < lo) ? lo : ((v > hi) ? hi : v);
}

static inline int RingProcessBottomY() {
  return ClampInt(RING_PROCESS_HEIGHT - 1, 0, uLCDH - 1);
}

static inline int ScaleYFrom60(int y_old) {
  // 旧代码按 0..59 行设计，这里映射到 0..RingProcessBottomY()。
  const float ratio = (float)RingProcessBottomY() / 59.0f;
  const int y_new = (int)(y_old * ratio + 0.5f);
  return ClampInt(y_new, 0, RingProcessBottomY());
}

static inline int ScaleXFrom80(int x_old) {
  // 旧代码按 0..79 列设计，这里映射到 0..(uLCDW-1)。
  const float ratio = (float)(uLCDW - 1) / 79.0f;
  const int x_new = (int)(x_old * ratio + 0.5f);
  return ClampInt(x_new, 0, uLCDW - 1);
}

static const RingParams& GetRingParams() {
  // 所有比例参数只计算一次，减少循环中的浮点开销。
  static const RingParams p = {
      ScaleYFrom60(10),   // offline_max_y
      ScaleYFrom60(30),   // straight_left_s_y
      ScaleYFrom60(25),   // straight_right_s_y
      ScaleYFrom60(45),   // straight_e_y
      ScaleYFrom60(52),   // precheck_y_start
      ScaleYFrom60(58),   // precheck_y_end

      ScaleYFrom60(25),   // detect_y_top
      ScaleYFrom60(58),   // detect_y_bottom
      ScaleXFrom80(4),    // jump_delta_x
      ScaleYFrom60(6),    // shape_gap_y
      ScaleYFrom60(3),    // shape_mid_y
      ScaleYFrom60(2),    // shape_near_y
      ScaleYFrom60(1),    // p2_gap_min_y

      ScaleYFrom60(59),   // center_apply_y_bottom
      ScaleYFrom60(55),   // state_num_scan_y_start
      ScaleYFrom60(30),   // state_num_scan_y_end
      ScaleYFrom60(3),    // state_w_seq_3
      ScaleYFrom60(2),    // state_w_seq_2
      ScaleYFrom60(13),   // state_offline_left_y
      ScaleYFrom60(16),   // state_offline_right_y
      ScaleYFrom60(45),   // state_finish_scan_top
      ScaleYFrom60(10),   // state_finish_scan_bottom
  };
  return p;
}

static inline int HalfRoadWidthAtRow(int y) {
  // 兼容处理: 优先使用当前行已识别宽度的一半，否则回退到屏宽 1/4。
  if (ImageDeal[y].Wide > 0) return ImageDeal[y].Wide / 2;
  return uLCDW / 4;
}

static inline bool IsWhiteFind(uint8 v) {
  return v == 'W';
}

static inline bool IsTrueFind(uint8 v) {
  return v == 'T';
}

static bool PreCheckForRing(RingSide side) {
  const RingParams& p = GetRingParams();
  // 旧阈值按 60 行图调过，这里做比例映射。
  const int line_hi_allow = (side == kLeft) ? 6 : 8;
  const int line_lo_need = 15;
  const int whiteline_max = 8;
  const int offline_max = p.offline_max_y;

  // 直道排除区间比例映射（旧: [30,45] / [25,45]）。
  const int straight_s = (side == kLeft) ? p.straight_left_s_y : p.straight_right_s_y;
  const int straight_e = p.straight_e_y;
  const int straight_flag = (side == kLeft) ? 2 : 1;
  extern float Straight_Judge(uint8 flag, int start, int end);

  if (side == kLeft) {
    if (ImageStatus.Right_Line > line_hi_allow ||
        ImageStatus.Left_Line < line_lo_need ||
        ImageStatus.OFFLine > offline_max ||
        Straight_Judge((uint8)straight_flag, straight_s, straight_e) > 1.0f ||
        ImageStatus.WhiteLine > whiteline_max) {
      return false;
    }
  } else {
    if (ImageStatus.Left_Line > line_hi_allow ||
        ImageStatus.Right_Line < line_lo_need ||
        ImageStatus.OFFLine > offline_max ||
        Straight_Judge((uint8)straight_flag, straight_s, straight_e) > 1.0f ||
        ImageStatus.WhiteLine > whiteline_max) {
      return false;
    }
  }

  // 连续近底部丢边快速排除（旧检查 52~58）。
  const int y_start = p.precheck_y_start;
  const int y_end = p.precheck_y_end;
  for (int y = y_start; y <= y_end; ++y) {
    if (side == kLeft && IsWhiteFind(ImageDeal[y].IsLeftFind)) return false;
    if (side == kRight && IsWhiteFind(ImageDeal[y].IsRightFind)) return false;
  }
  return true;
}

static bool DetectRingFeature(RingSide side, int* p1_y, int* p2_y) {
  const RingParams& p = GetRingParams();
  *p1_y = 0;
  *p2_y = 0;

  const int y_top = p.detect_y_top;
  const int y_bottom = p.detect_y_bottom;
  const int jump_delta = p.jump_delta_x;
  const int shape_gap = p.shape_gap_y;
  const int shape_mid = p.shape_mid_y;
  const int shape_near = p.shape_near_y;

  // 单次扫描同时寻找点1与点2，减少一次完整遍历。
  for (int y = y_bottom; y > y_top; --y) {
    if (side == kLeft) {
      if (*p1_y == 0 &&
          (ImageDeal[y].LeftBoundary_First - ImageDeal[y - 1].LeftBoundary_First > jump_delta)) {
        *p1_y = y;
      }
      if (*p2_y == 0 && y + 1 <= y_bottom &&
          (ImageDeal[y + 1].LeftBoundary - ImageDeal[y].LeftBoundary > jump_delta)) {
        *p2_y = y;
      }
    } else {
      if (*p1_y == 0 &&
          (ImageDeal[y - 1].RightBoundary_First - ImageDeal[y].RightBoundary_First > jump_delta)) {
        *p1_y = y;
      }
      if (*p2_y == 0 && y + 1 <= y_bottom &&
          (ImageDeal[y].RightBoundary - ImageDeal[y + 1].RightBoundary > jump_delta)) {
        *p2_y = y;
      }
    }
    if (*p1_y != 0 && *p2_y != 0) break;  // 两点都找到后立即停止
  }

  // 必要点未找到直接失败，避免后续无效扫描。
  if (*p1_y == 0 || *p2_y == 0) return false;

  // 几何辅助判定（原 Ring_Help_Flag）
  int help = 0;
  int y_scan_low = ClampInt(ImageStatus.OFFLine, 0, RingProcessBottomY());
  int y_scan_high = *p1_y;
  if (y_scan_high > shape_gap) {
    y_scan_high = ClampInt(y_scan_high, 0, RingProcessBottomY() - shape_gap);
    y_scan_low = ClampInt(y_scan_low, 0, y_scan_high - shape_gap);
    for (int y = y_scan_high; y > y_scan_low; --y) {
      if (side == kLeft) {
        if (ImageDeal[y + shape_gap].LeftBorder < ImageDeal[y + shape_mid].LeftBorder &&
            ImageDeal[y + shape_gap - 1].LeftBorder < ImageDeal[y + shape_mid].LeftBorder &&
            ImageDeal[y + shape_mid].LeftBorder > ImageDeal[y + shape_near].LeftBorder &&
            ImageDeal[y + shape_mid].LeftBorder > ImageDeal[y + 1].LeftBorder) {
          help = 1;
          break;
        }
      } else {
        if (ImageDeal[y + shape_gap].RightBorder > ImageDeal[y + shape_mid].RightBorder &&
            ImageDeal[y + shape_gap - 1].RightBorder > ImageDeal[y + shape_mid].RightBorder &&
            ImageDeal[y + shape_mid].RightBorder < ImageDeal[y + shape_near].RightBorder &&
            ImageDeal[y + shape_mid].RightBorder < ImageDeal[y + 1].RightBorder) {
          help = 1;
          break;
        }
      }
    }
  }

  // 后备触发: 特征点差满足且单侧丢边较多。
  if ((*p2_y > *p1_y + p.p2_gap_min_y) && help == 0) {
    if ((side == kLeft && ImageStatus.Left_Line > 7) ||
        (side == kRight && ImageStatus.Right_Line > 7)) {
      help = 1;
    }
  }

  return ((*p2_y > *p1_y + p.p2_gap_min_y) && help == 1);
}

static void ApplyPrepareRingCenter(RingSide side) {
  const RingParams& p = GetRingParams();
  // 准备进环阶段: 用可见边 + 半路宽估计中线
  const int y_bottom = ClampInt(p.center_apply_y_bottom, 0, RingProcessBottomY());
  const int y_offline = ClampInt(ImageStatus.OFFLine, 0, RingProcessBottomY());
  for (int y = y_bottom; y > y_offline; --y) {
    const int half_w = HalfRoadWidthAtRow(y);
    if (side == kLeft) {
      ImageDeal[y].Center = ImageDeal[y].RightBorder - half_w;
    } else {
      ImageDeal[y].Center = ImageDeal[y].LeftBorder + half_w;
    }
    ImageDeal[y].Center = ClampInt(ImageDeal[y].Center, 0, uLCDW - 1);
  }
}

static void ApplyPostRingCenter(RingSide side) {
  const RingParams& p = GetRingParams();
  // 出环后同样回到半宽估计中线
  const int y_bottom = ClampInt(p.center_apply_y_bottom, 0, RingProcessBottomY());
  const int y_offline = ClampInt(ImageStatus.OFFLine, 0, RingProcessBottomY());
  for (int y = y_bottom; y > y_offline; --y) {
    const int half_w = HalfRoadWidthAtRow(y);
    if (side == kLeft) {
      ImageDeal[y].Center = ImageDeal[y].RightBorder - half_w;
    } else {
      ImageDeal[y].Center = ImageDeal[y].LeftBorder + half_w;
    }
    ImageDeal[y].Center = ClampInt(ImageDeal[y].Center, 0, uLCDW - 1);
  }
}

static void UpdateRingStateMachine(RingSide side) {
  const RingParams& p = GetRingParams();
  // 统一的状态推进逻辑（按原代码语义保留阈值风格）
  int num_w = 0;
  const int y_start = p.state_num_scan_y_start;
  const int y_end = p.state_num_scan_y_end;
  const int dy3 = p.state_w_seq_3;
  const int dy2 = p.state_w_seq_2;
  for (int y = y_start; y > y_end; --y) {
    if (side == kLeft) {
      if (IsWhiteFind(ImageDeal[y].IsLeftFind)) ++num_w;
      if (IsWhiteFind(ImageDeal[y + dy3].IsLeftFind) &&
          IsWhiteFind(ImageDeal[y + dy2].IsLeftFind) &&
          IsWhiteFind(ImageDeal[y + 1].IsLeftFind) &&
          IsTrueFind(ImageDeal[y].IsLeftFind)) {
        break;
      }
    } else {
      if (IsWhiteFind(ImageDeal[y].IsRightFind)) ++num_w;
      if (IsWhiteFind(ImageDeal[y + dy3].IsRightFind) &&
          IsWhiteFind(ImageDeal[y + dy2].IsRightFind) &&
          IsWhiteFind(ImageDeal[y + 1].IsRightFind) &&
          IsTrueFind(ImageDeal[y].IsRightFind)) {
        break;
      }
    }
  }

  if (ImageFlag.image_element_rings_flag == 1 && num_w > 10) ImageFlag.image_element_rings_flag = 2;
  if (ImageFlag.image_element_rings_flag == 2 && num_w < ((side == kLeft) ? 8 : 5)) ImageFlag.image_element_rings_flag = 5;
  if (ImageFlag.image_element_rings_flag == 5 &&
      ((side == kLeft) ? (ImageStatus.Right_Line > 25) : (ImageStatus.Left_Line > 8))) {
    ImageFlag.image_element_rings_flag = 6;
  }
  if (ImageFlag.image_element_rings_flag == 6 &&
      ((side == kLeft) ? (ImageStatus.Right_Line < 3) : (ImageStatus.Left_Line < 3))) {
    ImageFlag.image_element_rings_flag = 7;
  }

  // 出环判据（简化保留原语义）
  if (ImageFlag.image_element_rings_flag == 8) {
    if ((side == kLeft && ImageStatus.Right_Line < 8 && ImageStatus.OFFLine < p.state_offline_left_y) ||
        (side == kRight && ImageStatus.Left_Line < 10 && ImageStatus.OFFLine < p.state_offline_right_y)) {
      ImageFlag.image_element_rings_flag = 9;
    }
  }

  if (ImageFlag.image_element_rings_flag == 9) {
    int num = 0;
    for (int y = p.state_finish_scan_top; y > p.state_finish_scan_bottom; --y) {
      if (side == kLeft && IsWhiteFind(ImageDeal[y].IsLeftFind)) ++num;
      if (side == kRight && IsWhiteFind(ImageDeal[y].IsRightFind)) ++num;
    }
    if (num < 5) {
      ImageStatus.Road_type = Normol;
      ImageFlag.image_element_rings_flag = 0;
      ImageFlag.image_element_rings = 0;
      ImageFlag.ring_big_small = 0;
    }
  }
}

}  // namespace

void Element_Judgment_Left_Rings_Portable(void) {
  if (!PreCheckForRing(kLeft)) return;
  int p1 = 0;
  int p2 = 0;
  if (DetectRingFeature(kLeft, &p1, &p2) && ImageFlag.image_element_rings_flag == 0) {
    ImageFlag.image_element_rings = 1;
    ImageFlag.image_element_rings_flag = 1;
    ImageFlag.ring_big_small = 1;
    ImageStatus.Road_type = LeftCirque;
  }
}

void Element_Judgment_Right_Rings_Portable(void) {
  if (!PreCheckForRing(kRight)) return;
  int p1 = 0;
  int p2 = 0;
  if (DetectRingFeature(kRight, &p1, &p2) && ImageFlag.image_element_rings_flag == 0) {
    ImageFlag.image_element_rings = 2;
    ImageFlag.image_element_rings_flag = 1;
    ImageFlag.ring_big_small = 1;
    ImageStatus.Road_type = RightCirque;
  }
}

void Element_Handle_Left_Rings_Portable(void) {
  UpdateRingStateMachine(kLeft);

  // 准备进环
  if (ImageFlag.image_element_rings_flag >= 1 && ImageFlag.image_element_rings_flag <= 4) {
    ApplyPrepareRingCenter(kLeft);
  }

  // 已出环
  if (ImageFlag.image_element_rings_flag == 9 || ImageFlag.image_element_rings_flag == 10) {
    ApplyPostRingCenter(kLeft);
  }
}

void Element_Handle_Right_Rings_Portable(void) {
  UpdateRingStateMachine(kRight);

  // 准备进环
  if (ImageFlag.image_element_rings_flag >= 1 && ImageFlag.image_element_rings_flag <= 4) {
    ApplyPrepareRingCenter(kRight);
  }

  // 已出环
  if (ImageFlag.image_element_rings_flag == 9 || ImageFlag.image_element_rings_flag == 10) {
    ApplyPostRingCenter(kRight);
  }
}

