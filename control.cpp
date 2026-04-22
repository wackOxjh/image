#include "control.hpp"
#include <math.h>

//纯跟踪 + 差速转向

// P I 参数
#define KP_SPEED 3.8f
#define KI_SPEED 0.9f
#define INTEGRAL_LIMIT 10.0f

static float speed_integral = 0.0f;

// 速度 PI 控制器
//example:          Speed_PI(vl, v, pwm_left);
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
//example：     PurePursuit_Diff(error, car.v, &pwm_left, &pwm_right);
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

//camera.cpp

static float lateral_error = 0.0f;  // 赛道中线误差

// 模拟提取赛道中线
void Image_Decode(void)
{
    // 实际工程：二值化 → 找左右边线 → 求中线
    // 这里给一个模拟误差
    lateral_error = 0.0f;
}

// 返回横向误差（单位 m）
float Get_Lateral_Error(void)
{
    return lateral_error;
}

// main.cpp
int main(void)
{
    // 初始化
    //?_init();
    /*参数初始化
    Pose_t car;
    car.x = 0;
    car.y = 0;
    car.yaw = 0;
    car.v = 0;*/ 

    float pwm_left = 0, pwm_right = 0;

    while (1)
    {
        // 1. 摄像头解码
        //获取图像：Image_Decode();
        float error = Get_Lateral_Error();

        // 2. 编码器测速
        float vl, vr;
        Calc_Speed(&vl, &vr);
        car.v = (vl + vr) / 2.0f;

        // 3. 纯跟踪差速控制
        PurePursuit_Diff(error, car.v, &pwm_left, &pwm_right);

        // 4. 输出 PWM 到电机
        // Set_PWM_L(pwm_left);
        // Set_PWM_R(pwm_right);
    }
}
