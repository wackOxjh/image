/**
 * Pure Pursuit 路径跟踪算法
 * 适用于 F 车模（后轮差速转向模型）
 * 
 * @author F车模纯跟踪实现
 * @date 2026
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 前视距离系数 k，建议取值 1.0~3.0，根据实际车速和赛道情况调整
#define K 2.0

// 最小前视距离 (m)
#define LD_MIN 0.4

// 最大前视距离 (m)
#define LD_MAX 1.2

// 最小角度阈值 (弧度)
#define ANGLE_THRESHOLD 0.01

// 最大转向角限制 (弧度)，通常不超过 30°
#define MAX_STEERING_ANGLE 0.5236

/**
 * 点结构体
 */
struct Point {
    double x, y;
    Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
};

/**
 * 车辆状态结构体
 */
struct VehicleState {
    double x;       // x 坐标 (m)
    double y;       // y 坐标 (m)
    double yaw;     // 航向角 (rad)
    double v;       // 速度 (m/s)
};

/**
 * PurePursuit 控制器类
 */
class PurePursuitController {
private:
    double wheelbase_;          // 轴距 (m)
    double lookahead_distance_; // 前视距离 (m)
    std::vector<Point> path_;   // 参考路径点
    
    /**
     * 计算两点间距离
     */
    double distance(const Point& p1, const Point& p2) const {
        return std::hypot(p1.x - p2.x, p1.y - p2.y);
    }
    
    /**
     * 动态计算前视距离
     * @param velocity 当前速度 (m/s)
     * @return 前视距离 (m)
     */
    double computeLookaheadDistance(double velocity) const {
        // 前视距离与速度成正比：Ld = k * v
        double ld = K * velocity;
        
        // 限制前视距离范围
        if (ld < LD_MIN) ld = LD_MIN;
        if (ld > LD_MAX) ld = LD_MAX;
        
        return ld;
    }
    
    /**
     * 在路径上寻找预瞄点
     * @param vehicle 当前车辆状态
     * @param lookahead_distance 前视距离
     * @return 预瞄点位置，若未找到则返回 false
     */
    bool findTargetPoint(const VehicleState& vehicle, double lookahead_distance, Point& target) const {
        if (path_.empty()) return false;
        
        // 找到距离车辆最近的点
        double min_dist = std::numeric_limits<double>::max();
        int nearest_idx = 0;
        for (size_t i = 0; i < path_.size(); ++i) {
            double d = distance(Point(vehicle.x, vehicle.y), path_[i]);
            if (d < min_dist) {
                min_dist = d;
                nearest_idx = i;
            }
        }
        
        // 从最近点向后寻找第一个超过前视距离的点
        for (size_t i = nearest_idx; i < path_.size(); ++i) {
            double d = distance(Point(vehicle.x, vehicle.y), path_[i]);
            if (d >= lookahead_distance) {
                target = path_[i];
                return true;
            }
        }
        
        // 若未找到，取最后一个路径点
        if (!path_.empty()) {
            target = path_.back();
            return true;
        }
        
        return false;
    }
    
    /**
     * 将角度归一化到 [-pi, pi] 范围
     */
    double normalizeAngle(double angle) const {
        while (angle > M_PI) angle -= 2.0 * M_PI;
        while (angle < -M_PI) angle += 2.0 * M_PI;
        return angle;
    }
    
public:
    /**
     * 构造函数
     * @param wheelbase 车辆轴距 (m)
     * @param path 参考路径点集
     */
    PurePursuitController(double wheelbase, const std::vector<Point>& path)
        : wheelbase_(wheelbase), path_(path) {}
    
    /**
     * 计算控制指令（转向角）
     * @param vehicle 当前车辆状态
     * @return 转向角 (rad)
     */
    double computeSteeringAngle(const VehicleState& vehicle) {
        // 1. 根据速度动态计算前视距离
        lookahead_distance_ = computeLookaheadDistance(vehicle.v);
        
        // 2. 寻找预瞄点
        Point target;
        if (!findTargetPoint(vehicle, lookahead_distance_, target)) {
            return 0.0;  // 无有效目标点，不转向
        }
        
        // 3. 计算 α 角（车辆朝向与车辆→目标点向量之间的夹角）
        double dx = target.x - vehicle.x;
        double dy = target.y - vehicle.y;
        
        // 目标点相对于车辆的角度
        double target_angle = std::atan2(dy, dx);
        
        // α = 目标点角度 - 车辆航向角
        double alpha = normalizeAngle(target_angle - vehicle.yaw);
        
        // 防止数值过小导致的计算异常
        if (std::abs(alpha) < ANGLE_THRESHOLD) {
            return 0.0;
        }
        
        // 4. 纯跟踪公式计算转向角
        double steering_angle = std::atan2(2.0 * wheelbase_ * std::sin(alpha), lookahead_distance_);
        
        // 5. 限制最大转向角
        if (steering_angle > MAX_STEERING_ANGLE) {
            steering_angle = MAX_STEERING_ANGLE;
        }
        if (steering_angle < -MAX_STEERING_ANGLE) {
            steering_angle = -MAX_STEERING_ANGLE;
        }
        
        return steering_angle;
    }
    
    /**
     * 获取当前前视距离（用于调试）
     */
    double getLookaheadDistance() const { return lookahead_distance_; }
    
    /**
     * 更新参考路径（动态路径更新）
     */
    void updatePath(const std::vector<Point>& new_path) { path_ = new_path; }
};

/**
 * F车模差速转向控制类
 * F车模采用双电机驱动，依靠后轮差速完成转向
 */
class FDifferentialSteering {
private:
    double track_width_;  // 轮距 (m)
    double max_speed_;    // 最大速度 (m/s)
    
public:
    FDifferentialSteering(double track_width, double max_speed = 3.0)
        : track_width_(track_width), max_speed_(max_speed) {}
    
    /**
     * 根据转向角和目标速度计算左右轮速度
     * @param steering_angle 转向角 (rad)
     * @param target_speed 目标速度 (m/s)
     * @return 左右轮速度 [left_speed, right_speed]
     */
    std::pair<double, double> computeWheelSpeeds(double steering_angle, double target_speed) {
        // 限制速度
        double speed = std::min(target_speed, max_speed_);
        
        // 阿克曼转向几何近似：转弯半径 R = wheelbase / tan(δ)
        // 差速转向：左轮速度 v_left = v * (R - track_width/2) / R
        //           右轮速度 v_right = v * (R + track_width/2) / R
        
        if (std::abs(steering_angle) < 0.01) {
            // 直行：左右轮速度相等
            return {speed, speed};
        }
        
        double R = 1.0 / std::tan(steering_angle);  // 转弯半径（轴距假设为 1）
        double left_speed = speed * (R - track_width_ / 2.0) / R;
        double right_speed = speed * (R + track_width_ / 2.0) / R;
        
        // 限制单轮速度不为负（不允许倒车，若需要倒车则单独处理）
        if (left_speed < 0) left_speed = 0;
        if (right_speed < 0) right_speed = 0;
        
        return {left_speed, right_speed};
    }
};

// ======================== 主程序示例 ========================
int main() {
    // 1. 定义参考路径（示例：简单的直线+曲线路径）
    std::vector<Point> path;
    for (double t = 0; t <= 10.0; t += 0.1) {
        double x = t;
        double y = 2.0 * std::sin(t * 0.8);
        path.emplace_back(x, y);
    }
    
    // 2. 初始化控制器（F车模轴距约为 0.25~0.3 m）
    PurePursuitController controller(0.28, path);
    
    // 3. 初始化差速转向控制器（F车模轮距约为 0.2~0.25 m）
    FDifferentialSteering diffSteering(0.22, 2.5);
    
    // 4. 模拟车辆初始状态
    VehicleState vehicle = {0.0, 0.0, 0.0, 1.0};  // 初始速度 1 m/s
    
    // 5. 主控制循环（示例：运行 200 个控制周期）
    const double dt = 0.05;  // 控制周期 50ms
    
    for (int step = 0; step < 200; ++step) {
        // 计算转向角
        double steering = controller.computeSteeringAngle(vehicle);
        
        // 计算左右轮速度指令
        auto [left_speed, right_speed] = diffSteering.computeWheelSpeeds(steering, 2.0);
        
        // 输出控制指令（此处仅打印，实际应发送到电机驱动）
        // printf("Step %3d | steering = %6.3f rad | left = %5.2f m/s | right = %5.2f m/s | Ld = %.3f\n",
        //        step, steering, left_speed, right_speed, controller.getLookaheadDistance());
        
        // 模拟车辆运动（简化的运动学更新）
        // 实际应用中，车辆的位姿更新由真实运动决定，此处仅为示例
        double v_avg = (left_speed + right_speed) / 2.0;
        double omega = (right_speed - left_speed) / 0.22;  // 角速度 = 差速 / 轮距
        
        vehicle.x += v_avg * std::cos(vehicle.yaw) * dt;
        vehicle.y += v_avg * std::sin(vehicle.yaw) * dt;
        vehicle.yaw += omega * dt;
        vehicle.yaw = std::atan2(std::sin(vehicle.yaw), std::cos(vehicle.yaw));
        vehicle.v = v_avg;
    }
    
    return 0;
}