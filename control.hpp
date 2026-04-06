#ifndef __CONTROL_HPP__
#define __CONTROL_HPP__

#include <stdint.h>

// F 车核心参数
#define WHEEL_BASE    0.155f   // 后轮距 m
#define LOOK_AHEAD_K  1.2f     // 预瞄系数
#define MIN_LOOK_AHEAD 0.10f   // 最小预瞄距离
#define MAX_SPEED     1.5f     // 最大速度 m/s
#define MIN_SPEED     0.4f     // 弯道最低速度
#define MAX_PWM       8000     // PWM 上限

// 车辆状态
typedef struct {
    float x;
    float y;
    float yaw;
    float v;          // 实际车速
    float v_left;
    float v_right;
} Pose_t;

// 路径点
typedef struct {
    float x;
    float y;
} PathPoint_t;

// 外部调用函数
void PurePursuit_Diff(float error, float v, float *pwm_left, float *pwm_right);
void Speed_PI(float target, float actual, float *pwm);

#endif