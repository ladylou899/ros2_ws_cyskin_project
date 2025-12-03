
#pragma once

#if ROS2_SUPPORT

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32_multi_array.hpp>
#include <vector>
#include <deque>
#include "skin_publisher.hpp"

class ROS2Publisher : public SkinPublisher, public rclcpp::Node 
{
private:
    rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr raw_data_pub_;
    std::deque<std::vector<float>> time_series_buffer_;
    std::vector<uint32_t> sensor_ids_;
    std::chrono::steady_clock::time_point start_time_;
    double collection_duration_;
    
public:
    ROS2Publisher(std::shared_ptr<UpdaterInterface> _u, double _thresh, double _publish_rate);
    ~ROS2Publisher();
    void publish() override;
    void collect_data_callback();
    void publish_timeseries();
};

#endif // ROS2_SUPPORT