#include "control.hpp"
#include "image.h"
#include <math.h>

//先从固定预锚点的纯跟踪算法入手，且不考虑速度。
//纯跟踪 + 差速转向

// P I 参数
#define KP_SPEED 3.8f
#define KI_SPEED 0.9f
#define INTEGRAL_LIMIT 10.0f    //积分限幅
#define AIM_DISTANCE    MIN_LOOK_AHEAD*300

static float speed_integral = 0.0f;     // 速度积分项
//lateral_error = 赛道中心线 - 车辆中心的横向偏移距离（单位 m）。*****它就是车有没有走歪的直接指标

// 速度 PI 控制器
//example:          Speed_PI(vl, v, pwm_left);
// target_v: 目标速度，actual_v: 实际速度；  pwm: “输出： PWM”            //前两项由编码器中Calc_Speed()计算得到
void Speed_PI(float target_v, float actual_v, float *pwm)
{
    float err = target_v - actual_v;
    speed_integral += err * 0.01f;
    // 积分限幅，防止积分过大导致控制器饱和
    if (speed_integral > INTEGRAL_LIMIT) speed_integral = INTEGRAL_LIMIT;
    if (speed_integral < -INTEGRAL_LIMIT) speed_integral = -INTEGRAL_LIMIT;

    float out = KP_SPEED * err + KI_SPEED * speed_integral;

    if (out > MAX_PWM) out = MAX_PWM;
    if (out < -MAX_PWM) out = -MAX_PWM;

    *pwm = out;
}

// 纯跟踪差速转向（F 车专用）
//example：     PurePursuit_Diff(error, car.v, &pwm_left, &pwm_right);
// lateral_error: 赛道中线误差（单位 m），v: 实际车速(由编码器)；  “输出：pwm_left/pwm_right:： PWM” 
void PurePursuit_Diff(float lateral_error, float v, float *pwm_left, float *pwm_right)
{
    // 1. 预瞄距离
    float Ld = MIN_LOOK_AHEAD;      // TEST版本：固定预瞄距离，简化控制器设计

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
    lateral_error = (ImageDeal[AIM_DISTANCE].Center - 60) * 0.1f;  // 在与固定预瞄点位（比如第30行的lateral_error）的 模拟误差：每像素对应 1 cm 的横向偏移
    // 这里给一个模拟误差    lateral_error = 0.0f;
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

/*# 一句话先讲透`lateral_error` = **赛道中心线 - 车辆中心的横向偏移距离**
它**不是凭空来的**，是 F 车控制系统里**最敏感、最核心、受最多因素影响**的变量。

我给你用**最直白、最接地气**的方式讲清楚：
**它受什么影响 → 为什么会变 → 怎么影响你的车跑不跑的稳**。

---

# 一、lateral_error 到底是什么？
简单理解：
- 赛道正中间是 0
- 车偏左 → error 为负
- 车偏右 → error 为正
- 数值越大 = 偏得越狠

它就是**车有没有走歪**的直接指标。

---

# 二、lateral_error 受哪些因素影响？（全总结）
一共 **6 大类影响源**，全部给你列全：

## 1）摄像头本身（最直接）
- 摄像头**安装高度**
- 摄像头**俯仰角度**（俯得太狠/太仰都会算错中线）
- 摄像头**左右倾斜**（歪了误差直接飘）
- 图像**二值化效果**（太亮/太暗找不到边线 → error 乱跳）
- 镜头**畸变**（近大远小，中线算不准）

**结论：摄像头装歪一点，error 直接乱跳。**

---

## 2）赛道环境（现场影响巨大）
- 赛道**光线变化**（阳光、阴影、灯光反射）
- 赛道**黑线模糊/磨损**
- 赛道**白色地面反光**
- 赛道**弯道曲率大小**
  - 急弯 → error 瞬间变大
  - 直道 → error 接近 0

---

## 3）车辆机械结构（F 车重点！）
F 车是**前万向轮 + 后双驱**，机械问题会直接导致 error 恒定偏移：

- 前轮**万向轮卡滞、不灵活**
- 后轮**两轮转速不一致**（电机差异）
- 车架**歪了**
- 重心**偏左/偏右**
- 轮子**大小不一样**
- 车底**摩擦不一样**

这些会导致：
**lateral_error 一直是正数 或 一直是负数 → 车一直跑偏**

---

## 4）车速（非常关键）
- 速度越快 → 车身响应越慢 → error 越大
- 速度越慢 → error 越小、越稳

所以纯跟踪里必须：
**速度快 → 预瞄远 → 抑制 error 突变**

---

## 5）控制算法（你代码里的参数）
你代码里的这些参数，会直接“修正” error：
- `Kp` 转向系数
- `Kd` 阻尼
- `LOOK_AHEAD_K` 预瞄系数
- `delta_v` 差速灵敏度

调得不好：
- 车**左右摆** → error 正负震荡
- 车**转向迟钝** → error 越来越大
- 车**太灵敏** → 小误差也疯狂修正

---

## 6）地面与打滑（F 车最容易出现）
F 车后驱，急加速/急减速会：
- 后轮打滑
- 车身侧滑
→ **瞬间产生巨大 lateral_error**

---

# 三、最核心总结（背下来就能调车）
## lateral_error 由 3 部分组成：
1. **真实物理偏移**（车真的歪了）
2. **摄像头测量误差**（没歪但看成歪了）
3. **运动滞后误差**（速度快导致跟不上）

---

# 四、你代码里 lateral_error 从哪来？（对应你工程）
```cpp
// 来自 camera.cpp
float Get_Lateral_Error(void)
{
    return lateral_error;
}
```

它是：
**摄像头图像处理 → 找到左右边线 → 计算中线 → 输出偏移**

所以：
### 图像 = 源头
### 机械 = 基础
### 算法 = 修正
### 车速 = 放大/缩小误差

---

# 五、我给你一个超实用判断口诀（F 车专用）
- **error 一直偏一边** → 机械/摄像头装歪
- **error 突然跳变** → 光线/赛道脏了
- **error 来回震荡** → 转向太灵敏 / Kp 太大
- **error 越来越大** → 预瞄太小 / 速度太快
- **error 稳定但不回零** → 中线算法不准

---

# 六、如果你愿意，我可以下一步帮你：
1. **写一个真正能跑的摄像头中线提取算法**（二值化 + 边缘检测 + 中线计算）
2. **教你如何校准 lateral_error**
3. **给你加一个误差滤波，让车不抖、不飘**
*/
