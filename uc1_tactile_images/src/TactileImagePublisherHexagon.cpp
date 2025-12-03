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

        cv::resize(I, I_resized, cv::Size(500, 500));

        cv::imshow("Tactile Image Hexagon", I_resized);

        cv::waitKey(1);
    }

    u.stopRobotSkinUpdater();

    return 0;
}
