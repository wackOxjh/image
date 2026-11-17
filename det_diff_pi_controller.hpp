#ifndef DET_DIFF_PI_CONTROLLER_HPP
#define DET_DIFF_PI_CONTROLLER_HPP

#include "image.h"

// 中线 PI 参数（用于中线误差 -> 差速 PWM）
#define DET_DIFF_PI_KP (4.0f)  // 比例系数：越大转向响应越快
#define DET_DIFF_PI_KI (1.0f)  // 积分系数：用于消除长期偏差

#ifdef __cplusplus
extern "C" {
#endif

void GetDet(void);

#ifdef __cplusplus
}
#endif

typedef struct {
  float kp;
  float ki;
  float integral_limit;
  float output_limit;
  float det_to_speed_gain;
  float base_speed;
  float min_wheel_speed;
  float max_wheel_speed;
  float pwm_min;
  float pwm_max;
} DetDiffPiConfig;

typedef struct {
  float i_left;
  float i_right;
  float i_center;
  float det_error;
} DetDiffPiState;

typedef struct {
  float det_error;
  float target_left_speed;
  float target_right_speed;
  float pwm_left;
  float pwm_right;
} DetDiffPiOutput;

void DetDiffPi_SetDefaultConfig(DetDiffPiConfig *cfg);
void DetDiffPi_Reset(DetDiffPiState *state);
float DetDiffPi_GetDetError(void);
void DetDiffPi_Update(const DetDiffPiConfig *cfg,
                      DetDiffPiState *state,
                      float actual_left_speed,
                      float actual_right_speed,
                      float dt_s,
                      DetDiffPiOutput *out);

void DetDiffPi_UpdateCenterLinePwm(const DetDiffPiConfig *cfg,
                                   DetDiffPiState *state,
                                   float base_pwm,
                                   float dt_s,
                                   DetDiffPiOutput *out);

#ifdef __cplusplus
}
#endif

#endif
