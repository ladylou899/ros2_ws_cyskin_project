
#include "ros_publisher.hpp"
#include <thread>

#if ROS2_SUPPORT

ROS2Publisher::ROS2Publisher(std::shared_ptr<UpdaterInterface> _u, double _thresh, double _publish_rate)
    : SkinPublisher(), Node("cyskin_acquisition_node"), collection_duration_(3.0)
{
    u = _u;
    thresh = _thresh;
    print_freq = _publish_rate;
    
    raw_data_pub_ = this->create_publisher<std_msgs::msg::Float32MultiArray>("/cyskin/timeseries_data", 10);
    start_time_ = std::chrono::steady_clock::now();
    
    RCLCPP_INFO(this->get_logger(), "CySkin ROS2 Publisher ready - collecting 3s windows at 10Hz");
}

ROS2Publisher::~ROS2Publisher()
{
    RCLCPP_INFO(this->get_logger(), "CySkin ROS2 Publisher shutdown");
}

void ROS2Publisher::publish()
{
    std::cout << "Writing skin data on ROS 2" << std::endl;
    
    while (rclcpp::ok() && u->isRunning()) {
        collect_data_callback();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // 10Hz
        rclcpp::spin_some(shared_from_this());
    }
}

void ROS2Publisher::collect_data_callback()
{
    auto data = u->getDataBuffer();
    const size_t n = u->getNumberOfSensors();
    
    // Basic validation
    if (data.empty() || data.size() < 2*n || n == 0) return;
    
    // Get sensor IDs and values (simple - no complex initialization)
    if (sensor_ids_.size() != n) {
        sensor_ids_.clear();
        for (size_t i = 0; i < n; ++i) {
            sensor_ids_.push_back(data[i]);
        }
        RCLCPP_INFO(this->get_logger(), "Updated to %zu sensors", n);
    }
    
    // Collect current values
    std::vector<float> values;
    for (size_t i = 0; i < n; ++i) {
        values.push_back(static_cast<float>(data[i + n]));
    }
    time_series_buffer_.push_back(values);
    
    // Publish every 3 seconds (30 samples at 10Hz)
    auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(
        std::chrono::steady_clock::now() - start_time_).count();
        
    if (elapsed >= 3.0) {
        publish_timeseries();
        sensor_ids_.clear();
        time_series_buffer_.clear();
        start_time_ = std::chrono::steady_clock::now();
    }
}

void ROS2Publisher::publish_timeseries()
{
    if (time_series_buffer_.empty()) return;
    
    auto msg = std_msgs::msg::Float32MultiArray();
    
    // Simple format: [sensor_ids..., timestep1_values..., timestep2_values...]
    for (uint32_t id : sensor_ids_) {
        msg.data.push_back(static_cast<float>(id));
    }
    
    for (const auto& timestep : time_series_buffer_) {
        for (float value : timestep) {
            msg.data.push_back(value);
        }
    }
    
    raw_data_pub_->publish(msg);
    RCLCPP_INFO(this->get_logger(), "Published: %zu sensors × %zu timesteps", 
                sensor_ids_.size(), time_series_buffer_.size());
}

#endif // ROS2_SUPPORT