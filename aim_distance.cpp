#include "aim_distance.h"
#include <cmath>

#define pixel_per_meter 100.0f
#define ROAD_WIDTH      (0.45)
#define MT9V03X_CSI_W  (160)
#define MT9V03X_CSI_H  (120)
#define POINTS_MAX_LEN  (MT9V03X_CSI_H)
#define FAR_POINTS_MAX_LEN  (POINTS_MAX_LEN)
#define dist (pixel_per_meter * ROAD_WIDTH / 2)         //单位像素乘以半个赛道宽
#define SMOTOR_RATE     (2.4)                           // 前轮转角和方向舵机转角的比例关系
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MINMAX(input, low, upper) MIN(MAX(input, low), upper)
#ifndef PI
  #define PI               3.14159265358979f
#endif
float aim_distance = 0.68;
float sample_dist = 0.02;
float rptsn[POINTS_MAX_LEN][2];
float mapy[240][376];
float mapx[240][376];

float angle;                    //舵机控制偏差
int rptsn_num;
struct aim_distance
{
    float aim1 = 0.58;      //直道/常规
    float aim2 = 0.4;       //十字路口
    float aim3 = 0.25;      //适合小半径转弯
    float aim4 = 0.68;
};
typedef struct {
    float kp;    //P
    float ki;    //I
    float kd;    //D
    float i_max; //integrator_max
    float p_max; //integrator_max
    float d_max; //integrator_max

    float low_pass;

    float out_p;
    float out_i;
    float out_d;

    float error;
    float pre_error;
    float pre_pre_error;
} pid_param_t;

// 车轮对应点(纯跟踪起始点)
float cx = mapx[(int) (MT9V03X_CSI_H * 0.78f)][MT9V03X_CSI_W / 2];
float cy = mapy[(int) (MT9V03X_CSI_H * 0.78f)][MT9V03X_CSI_W / 2];
// 常规PID
float pid_solve(pid_param_t *pid, float error) {
    pid->out_d = (error - pid->out_p) * pid->low_pass + pid->out_d * (1 - pid->low_pass);
    pid->out_p = error;
    pid->out_i += error;

    if (pid->ki != 0) pid->out_i = MINMAX(pid->out_i, -pid->i_max / pid->ki, pid->i_max / pid->ki);

    return pid->kp * pid->out_p + pid->ki * pid->out_i + pid->kd * pid->out_d;
}

//舵机控制PID
pid_param_t servo_pid = PID_CREATE(1.5, 0, 1.0, 0.8, 15, 5, 15);
int clip(int x, int low, int up) {
    return x > up ? up : x < low ? low : x;
}

// 左边线跟踪中线
void track_leftline(float pts_in[][2], int num, float pts_out[][2], int approx_num, float dist) {
    for (int i = 0; i < num; i++) {
        float dx = pts_in[clip(i + approx_num, 0, num - 1)][0] - pts_in[clip(i - approx_num, 0, num - 1)][0];
        float dy = pts_in[clip(i + approx_num, 0, num - 1)][1] - pts_in[clip(i - approx_num, 0, num - 1)][1];
        float dn = sqrt(dx * dx + dy * dy);         //开根号25->5。
        dx /= dn;
        dy /= dn;
        pts_out[i][0] = pts_in[i][0] - dy * dist;
        pts_out[i][1] = pts_in[i][1] + dx * dist;
    }
}

// 右边线跟踪中线
void track_rightline(float pts_in[][2], int num, float pts_out[][2], int approx_num, float dist) {
    for (int i = 0; i < num; i++) {
        float dx = pts_in[clip(i + approx_num, 0, num - 1)][0] - pts_in[clip(i - approx_num, 0, num - 1)][0];
        float dy = pts_in[clip(i + approx_num, 0, num - 1)][1] - pts_in[clip(i - approx_num, 0, num - 1)][1];
        float dn = sqrt(dx * dx + dy * dy);
        dx /= dn;
        dy /= dn;
        pts_out[i][0] = pts_in[i][0] + dy * dist;
        pts_out[i][1] = pts_in[i][1] - dx * dist;
    }
}

// 远预锚点位置
int aim_idx = clip(round(aim_distance / sample_dist), 0, rptsn_num - 1);
// 近预锚点位置
int aim_idx_near = clip(round(0.25 / sample_dist), 0, rptsn_num - 1);
//中线 rptsn 是等距采样的，每两个相邻点间距 sample_dist 米。所以：aim_distance / sample_dist = 沿中线往前数多少个采样点，这就是远预锚点的索引
//近预锚点固定取 0.25m 处的点。clip 防止越界。

// 计算远锚点偏差值
float dx = rptsn[aim_idx][0] - cx;
float dy = cy - rptsn[aim_idx][1] + 0.2 * pixel_per_meter;
float dn = sqrt(dx * dx + dy * dy);
float error = -atan2f(dx, dy) * 180 / PI;

// 纯跟踪算法(只考虑远点)
float pure_angle = -atanf(pixel_per_meter * 2 * 0.2 * dx / dn / dn) / PI * 180 / SMOTOR_RATE;
angle = pid_solve(&servo_pid, pure_angle);
angle = MINMAX(angle, -14.5, 14.5);
