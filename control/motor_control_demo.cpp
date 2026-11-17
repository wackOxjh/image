#include "motor_control.hpp"

#include <stdio.h>
#include <unistd.h>

#include "lq_common.hpp"

// 示例：把视觉同学给的数据填进这里。
// 实车时建议由视觉线程/进程更新共享变量，电机控制线程只读取最新一帧结果。
static zmg::VisionInfo get_vision_info_from_camera(void)
{
    zmg::VisionInfo info;
    info.error = 0.0f;
    info.road_type = zmg::RoadType::STRAIGHT;
    info.line_lost = false;
    info.need_slow = false;
    info.need_stop = false;
    return info;
}

void zmg_motor_control_demo(void)
{
    zmg::MotorControlConfig config = zmg::default_motor_control_config();

    // 先低速小 PWM 偏移上车调试，确认 5000 停车、方向、编码器正负号和急停都正确后再提速。
    // 想改“基础速度”：直道改 straight_speed，弯道改 curve_speed；need_slow=true 时会再乘 slow_ratio。
    config.straight_speed = 5.0f;  // 直道基础速度
    config.curve_speed = 3.5f;     // 弯道基础速度
    config.max_reverse_speed = 2.0f;
    config.min_run_pwm_offset = 250;
    config.max_pwm_offset_from_mid = 1800; // duty 限制为 3200..6800，确认安全后再逐步增大。

    zmg::MotorController motor(config);

    while (ls_system_running.load()) {
        const zmg::VisionInfo vision = get_vision_info_from_camera();
        motor.update(vision);

        const zmg::MotorControlDebug& dbg = motor.debug();
        // encL/encR 就是 dbg.left_measured_speed/right_measured_speed：
        // 左右编码器采集并换算出的速度反馈值。
        printf("base=%5.2f turn=%5.2f targetL=%5.2f targetR=%5.2f encL=%5.2f encR=%5.2f boff=%5d loff=%5d roff=%5d dutyL=%5d dutyR=%5d lost=%u\n",
            dbg.base_target_speed,
            dbg.turn_target_speed,
            dbg.left_target_speed,
            dbg.right_target_speed,
            dbg.left_measured_speed,
            dbg.right_measured_speed,
            dbg.base_pwm_offset,
            dbg.left_pwm_offset,
            dbg.right_pwm_offset,
            dbg.left_duty,
            dbg.right_duty,
            dbg.lost_line_count);

        usleep((useconds_t)(config.control_period_s * 1000000.0f));
    }

    // 退出前再次保持 50% duty 和 ENABLE 高，避免底层 PWM cleanup 输出危险的 0% duty。
    motor.safe_shutdown();
}
