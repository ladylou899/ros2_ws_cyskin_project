#include "rsl_typenames.hpp"
#include "robot_skin.hpp"
#include "skin_updater_from_file.hpp"
#include "skin_updater_from_shm.hpp"
#include "tactile_image_builder.hpp"
#include "tactile_map.hpp"

#include <rclcpp/rclcpp.hpp>
#include <cv_bridge/cv_bridge.hpp>
#include <sensor_msgs/msg/image.hpp>
#include "uc1_tactile_images/msg/image_array_link.hpp"
#include <deque>
#include <chrono>
#include <filesystem>

using namespace rsl;

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cout << "Error: insert the calibration file path\n";
        return -1;
    }
    else if (argc > 2)
    {
        std::cout << "Error: Too many arguments in input\n";
        return -1;
    }

    auto ctx = std::make_shared<rclcpp::Context>();                
    ctx->init(argc, argv);                                         
    auto node = std::make_shared<rclcpp::Node>(                    
        "tactile_image_publisher_min",
        rclcpp::NodeOptions().context(ctx));    

    // Create the RobotSkin object.
    RobotSkin S = RobotSkin(std::string(argv[1]));
    SkinUpdaterFromShMem u(S);
    u.startRobotSkinUpdater();

    // build tactile maps from sub-patches
    float tmap_resolution = 0.001;
    TactileMap T(S, 0);

    TactileImageBuilder *TIB = new TactileImageBuilder(T, tmap_resolution);

    TIB->buildTactileImage();

    cv::Mat I;
    cv::Mat I_resized;
    
    // Gesture recording setup
    std::deque<cv::Mat> frame_buffer;
    const int GESTURE_DURATION_SEC = 3;
    const int FPS = 30; // Approximate frame rate
    const int MAX_FRAMES = GESTURE_DURATION_SEC * FPS;
    bool recording = false;
    bool was_touching = false;
    int gesture_count = 0;
    
    // Create gesture output directory
    std::filesystem::create_directories("./gesture_data");
    
    std::cout << "Manual Gesture Recording Mode:" << std::endl;
    std::cout << "- Perform gestures on the sensor" << std::endl;
    std::cout << "- Press SPACEBAR to save the last 3 seconds as max projection image" << std::endl;
    std::cout << "- Press 'q' to quit" << std::endl;
    std::cout << "- Images saved to ./gesture_data/" << std::endl;

    // Create the TactileImageBuilder using 1 mm of spatial resolution.
    // TactileImageBuilder *TIB = new TactileImageBuilder(T,0.001);

    // Build the Tactile Image in background.
    // TIB->buildTactileImage();

    // Display the Tactile Image
    // cv::Mat I;
    // cv::Mat I_resized;

    while (1)
    {
        u.makeThisThreadWaitForNewData();

        I = TIB->getTactileImageCV();
        
        // Convert to grayscale if needed (tactile images should already be grayscale)
        cv::Mat I_gray;
        if (I.channels() == 3) {
            cv::cvtColor(I, I_gray, cv::COLOR_BGR2GRAY);
        } else {
            I_gray = I.clone();
        }
        
        // Always buffer frames (for manual gesture capture)
        frame_buffer.push_back(I_gray.clone());
        
        // Keep buffer size to 3 seconds worth of frames
        if (frame_buffer.size() > MAX_FRAMES) {
            frame_buffer.pop_front();
        }
        

        
        // Display current frame with buffer status
        cv::resize(I, I_resized, cv::Size(500, 500));
        
        // Show buffer status and instructions
        cv::putText(I_resized, "Buffer: " + std::to_string(frame_buffer.size()) + "/" + std::to_string(MAX_FRAMES), 
                   cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
        cv::putText(I_resized, "Gestures saved: " + std::to_string(gesture_count), 
                   cv::Point(10, 60), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
        cv::putText(I_resized, "Press SPACE to save gesture", 
                   cv::Point(10, I_resized.rows - 50), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 255, 0), 2);
        cv::putText(I_resized, "Press 'q' to quit", 
                   cv::Point(10, I_resized.rows - 20), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 2);
        
        cv::imshow("Tactile Gesture Recorder", I_resized);
        
        // Keyboard controls
        char key = cv::waitKey(1);
        if (key == 'q') {
            std::cout << "Quitting... Total gestures saved: " << gesture_count << std::endl;
            break;
        }
        if (key == ' ' && !frame_buffer.empty()) {
            // Generate max projection from current buffer
            cv::Mat max_projection = frame_buffer[0].clone();
            for (size_t i = 1; i < frame_buffer.size(); i++) {
                cv::max(max_projection, frame_buffer[i], max_projection);
            }
            
            // Save gesture image
            std::string filename = "./gesture_data/gesture_" + 
                                 std::to_string(gesture_count) + "_maxproj.png";
            cv::imwrite(filename, max_projection);
            
            std::cout << "Gesture " << gesture_count << " saved! (" 
                      << frame_buffer.size() << " frames) -> " << filename << std::endl;
            
            gesture_count++;
        }
    }

    u.stopRobotSkinUpdater();

    return 0;
}
