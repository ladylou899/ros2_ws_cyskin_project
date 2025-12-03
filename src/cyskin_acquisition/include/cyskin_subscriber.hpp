#pragma once

#if ROS2_SUPPORT

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32_multi_array.hpp>
#include <vector>

class CySkinSubscriber : public rclcpp::Node
{
private:
    rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr subscription_;
    std::string output_filename_;
    int message_count_;
    
public:
    CySkinSubscriber();
    ~CySkinSubscriber();
    
private:
    void data_callback(const std_msgs::msg::Float32MultiArray::SharedPtr msg);
    void analyze_data(const std::vector<float>& data);
};

#endif // ROS2_SUPPORT