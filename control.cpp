#include "control.h"
#include <math.h>

// PI 参数
#define KP_SPEED 3.8f
#define KI_SPEED 0.9f
#define INTEGRAL_LIMIT 10.0f

static float speed_integral = 0.0f;

// 速度 PI 控制器
void Speed_PI(float target_v, float actual_v, float *pwm)
{
    float err = target_v - actual_v;
    speed_integral += err * 0.01f;

    if (speed_integral > INTEGRAL_LIMIT) speed_integral = INTEGRAL_LIMIT;
    if (speed_integral < -INTEGRAL_LIMIT) speed_integral = -INTEGRAL_LIMIT;

    float out = KP_SPEED * err + KI_SPEED * speed_integral;

    if (out > MAX_PWM) out = MAX_PWM;
    if (out < -MAX_PWM) out = -MAX_PWM;

    *pwm = out;
}

// 纯跟踪差速转向（F 车专用）
void PurePursuit_Diff(float lateral_error, float v, float *pwm_left, float *pwm_right)
{
    // 1. 预瞄距离
    float Ld = LOOK_AHEAD_K * v;
    if (Ld < MIN_LOOK_AHEAD) Ld = MIN_LOOK_AHEAD;

    // 2. 等效 alpha（用横向误差近似）
    float alpha = lateral_error * 2.5f;

    // 3. 转向量
    float delta = atan2f(2.0f * WHEEL_BASE * sinf(alpha), Ld);

    // 4. 差速量
    float delta_v = delta * 0.32f;

    // 5. 动态限速（曲率越大越慢）
    float curv = fabs(2.0f * sinf(alpha) / Ld);
    float target_v = MAX_SPEED / (1.0f + 6.0f * curv);
    if (target_v < MIN_SPEED) target_v = MIN_SPEED;

    // 6. 左右轮目标速度
    float vl = target_v - delta_v;
    float vr = target_v + delta_v;

    // 7. PI 输出 PWM
    Speed_PI(vl, v, pwm_left);
    Speed_PI(vr, v, pwm_right);
}