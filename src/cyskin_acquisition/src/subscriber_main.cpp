#include "cyskin_subscriber.hpp"

#if ROS2_SUPPORT

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    
    auto subscriber = std::make_shared<CySkinSubscriber>();
    
    std::cout << "Starting CySkin subscriber... Press Ctrl+C to stop" << std::endl;
    
    try {
        rclcpp::spin(subscriber);
    } catch (const std::exception& e) {
        RCLCPP_ERROR(subscriber->get_logger(), "Exception: %s", e.what());
    }
    
    rclcpp::shutdown();
    return 0;
}

#else

int main()
{
    std::cout << "ROS2 support not enabled. Please compile with ROS2 support." << std::endl;
    return -1;
}

#endif // ROS2_SUPPORT