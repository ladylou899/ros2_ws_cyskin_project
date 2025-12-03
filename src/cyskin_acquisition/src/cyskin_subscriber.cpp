#include "cyskin_subscriber.hpp"
#include <fstream>
#include <iomanip>
#include <chrono>

#if ROS2_SUPPORT

CySkinSubscriber::CySkinSubscriber() : Node("cyskin_subscriber"), message_count_(0)
{
    subscription_ = this->create_subscription<std_msgs::msg::Float32MultiArray>(
        "/cyskin/timeseries_data",
        10,
        std::bind(&CySkinSubscriber::data_callback, this, std::placeholders::_1)
    );
    
    // Create output file with timestamp
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << "cyskin_data_" << std::put_time(std::localtime(&time_t), "%Y%m%d_%H%M%S") << ".txt";
    output_filename_ = ss.str();
    
    RCLCPP_INFO(this->get_logger(), "CySkin Subscriber started - listening to /cyskin/timeseries_data");
    RCLCPP_INFO(this->get_logger(), "Saving data to: %s", output_filename_.c_str());
}

CySkinSubscriber::~CySkinSubscriber()
{
    RCLCPP_INFO(this->get_logger(), "CySkin Subscriber shutdown");
}

void CySkinSubscriber::data_callback(const std_msgs::msg::Float32MultiArray::SharedPtr msg)
{
    std::vector<float> data = msg->data;
    analyze_data(data);
}

void CySkinSubscriber::analyze_data(const std::vector<float>& data)
{
    message_count_++;
    
    RCLCPP_INFO(this->get_logger(), "Message #%d: Received %zu elements", message_count_, data.size());
    
    // Save all data to file
    std::ofstream file(output_filename_, std::ios::app);
    if (file.is_open()) {
        // Write header for each message
        file << "# Message " << message_count_ << " - " << data.size() << " elements\n";
        
        // Write all data values (80 per line for readability)
        for (size_t i = 0; i < data.size(); ++i) {
            file << data[i];
            if ((i + 1) % 40 == 0) {
                file << "\n";  // New line every 40 values
            } else if (i < data.size() - 1) {
                file << " ";   // Space between values
            }
        }
        file << "\n\n";  // Extra line between messages
        file.close();
    } else {
        RCLCPP_ERROR(this->get_logger(), "Failed to open file: %s", output_filename_.c_str());
    }
}

#endif // ROS2_SUPPORT