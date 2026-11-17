#include "det_diff_pi_controller.hpp"

static float DetDiffPi_Clamp(float value, float low, float high) {
  if (value < low) {
    return low;
  }
  if (value > high) {
    return high;
  }
  return value;
}

static float DetDiffPi_SolvePi(float target,
                               float actual,
                               float dt_s,
                               float kp,
                               float ki,
                               float integral_limit,
                               float output_limit,
                               float *integral_state) {
  float error = target - actual;

  *integral_state += error * dt_s;
  *integral_state = DetDiffPi_Clamp(*integral_state, -integral_limit, integral_limit);

  float output = kp * error + ki * (*integral_state);
  return DetDiffPi_Clamp(output, -output_limit, output_limit);
}

void DetDiffPi_SetDefaultConfig(DetDiffPiConfig *cfg) {
  if (cfg == 0) {
    return;
  }

  cfg->kp = DET_DIFF_PI_KP;
  cfg->ki = DET_DIFF_PI_KI;
  cfg->integral_limit = 30.0f;
  cfg->output_limit = 8000.0f;
  cfg->det_to_speed_gain = 0.015f;
  cfg->base_speed = 1.0f;
  cfg->min_wheel_speed = 0.2f;
  cfg->max_wheel_speed = 1.8f;
  cfg->pwm_min = -8000.0f;
  cfg->pwm_max = 8000.0f;
}

void DetDiffPi_Reset(DetDiffPiState *state) {
  if (state == 0) {
    return;
  }

  state->i_left = 0.0f;
  state->i_right = 0.0f;
  state->i_center = 0.0f;
  state->det_error = 0.0f;
}

float DetDiffPi_GetDetError(void) {
  GetDet();
  return (float)ImageStatus.Det_True - (float)ImageSensorMid;
}

void DetDiffPi_Update(const DetDiffPiConfig *cfg,
                      DetDiffPiState *state,
                      float actual_left_speed,
                      float actual_right_speed,
                      float dt_s,
                      DetDiffPiOutput *out) {
  if (cfg == 0 || state == 0 || out == 0) {
    return;
  }

  if (dt_s <= 0.0f) {
    dt_s = 0.01f;
  }

  state->det_error = DetDiffPi_GetDetError();

  float turn_delta = state->det_error * cfg->det_to_speed_gain;
  float left_target = cfg->base_speed - turn_delta;
  float right_target = cfg->base_speed + turn_delta;

  left_target = DetDiffPi_Clamp(left_target, cfg->min_wheel_speed, cfg->max_wheel_speed);
  right_target = DetDiffPi_Clamp(right_target, cfg->min_wheel_speed, cfg->max_wheel_speed);

  out->det_error = state->det_error;
  out->target_left_speed = left_target;
  out->target_right_speed = right_target;
  out->pwm_left = DetDiffPi_SolvePi(left_target,
                                    actual_left_speed,
                                    dt_s,
                                    cfg->kp,
                                    cfg->ki,
                                    cfg->integral_limit,
                                    cfg->output_limit,
                                    &state->i_left);
  out->pwm_right = DetDiffPi_SolvePi(right_target,
                                     actual_right_speed,
                                     dt_s,
                                     cfg->kp,
                                     cfg->ki,
                                     cfg->integral_limit,
                                     cfg->output_limit,
                                     &state->i_right);
}

void DetDiffPi_UpdateCenterLinePwm(const DetDiffPiConfig *cfg,
                                   DetDiffPiState *state,
                                   float base_pwm,
                                   float dt_s,
                                   DetDiffPiOutput *out) {
  if (cfg == 0 || state == 0 || out == 0) {
    return;
  }

  if (dt_s <= 0.0f) {
    dt_s = 0.01f;
  }

  state->det_error = DetDiffPi_GetDetError();

  state->i_center += state->det_error * dt_s;
  state->i_center =
      DetDiffPi_Clamp(state->i_center, -cfg->integral_limit, cfg->integral_limit);

  // 仅对中线误差做 PI，输出为左右轮差速 PWM
  float turn_pwm = cfg->kp * state->det_error + cfg->ki * state->i_center;
  turn_pwm = DetDiffPi_Clamp(turn_pwm, -cfg->output_limit, cfg->output_limit);

  out->det_error = state->det_error;
  out->target_left_speed = 0.0f;
  out->target_right_speed = 0.0f;
  out->pwm_left = DetDiffPi_Clamp(base_pwm - turn_pwm, cfg->pwm_min, cfg->pwm_max);
  out->pwm_right = DetDiffPi_Clamp(base_pwm + turn_pwm, cfg->pwm_min, cfg->pwm_max);
}
