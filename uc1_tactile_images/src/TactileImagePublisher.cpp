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

    // tactile images publishers (one per each link)
    auto pub_link1 = node->create_publisher<uc1_tactile_images::msg::ImageArrayLink>(
        "uc1_tactile_images/link1", rclcpp::QoS(10).best_effort());
    auto pub_link2 = node->create_publisher<uc1_tactile_images::msg::ImageArrayLink>(
        "uc1_tactile_images/link2", rclcpp::QoS(10).best_effort());

    auto to_ros_img = [&](const cv::Mat &img, const std::string &frame_id)
    {
        std_msgs::msg::Header h;
        h.stamp = node->now();
        h.frame_id = frame_id;
        const char *enc = (img.channels() == 1) ? "mono8" : "bgr8"; // adjust if needed
        return *cv_bridge::CvImage(h, enc, img).toImageMsg();
    };

    // build tactile maps from sub-patches
    float tmap_resolution = 0.001;
    TactileMap T1(S, 0);
    TactileMap T2(S, 1);
    TactileMap T3(S, 2);
    TactileMap T4(S, 3);
    TactileMap T5(S, 4);
    TactileMap T6(S, 5);
    TactileMap T7(S, 6);
    TactileMap T8(S, 7);

    TactileImageBuilder *TIB1 = new TactileImageBuilder(T1, tmap_resolution);
    TactileImageBuilder *TIB2 = new TactileImageBuilder(T2, tmap_resolution);
    TactileImageBuilder *TIB3 = new TactileImageBuilder(T3, tmap_resolution);
    TactileImageBuilder *TIB4 = new TactileImageBuilder(T4, tmap_resolution);
    TactileImageBuilder *TIB5 = new TactileImageBuilder(T5, tmap_resolution);
    TactileImageBuilder *TIB6 = new TactileImageBuilder(T6, tmap_resolution);
    TactileImageBuilder *TIB7 = new TactileImageBuilder(T7, tmap_resolution);
    TactileImageBuilder *TIB8 = new TactileImageBuilder(T8, tmap_resolution);

    TIB1->buildTactileImage();
    TIB2->buildTactileImage();
    TIB3->buildTactileImage();
    TIB4->buildTactileImage();
    TIB5->buildTactileImage();
    TIB6->buildTactileImage();
    TIB7->buildTactileImage();
    TIB8->buildTactileImage();

    cv::Mat I1, I2, I3, I4, I5, I6, I7, I8;
    cv::Mat I1_resized, I2_resized, I3_resized, I4_resized, I5_resized, I6_resized, I7_resized, I8_resized;

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

        std::vector<cv::Mat> link1_images;
        std::vector<cv::Mat> link2_images;

        // I = TIB->getTactileImageCV();

        // cv::resize(I, I_resized, cv::Size(500,500));

        // cv::imshow("Tactile Image ", I_resized);

        I1 = TIB1->getTactileImageCV();
        link1_images.push_back(I1);
        I2 = TIB2->getTactileImageCV();
        link1_images.push_back(I2);
        I3 = TIB3->getTactileImageCV();
        link1_images.push_back(I3);
        I4 = TIB4->getTactileImageCV();
        link1_images.push_back(I4);
        I5 = TIB5->getTactileImageCV();
        link2_images.push_back(I5);
        I6 = TIB6->getTactileImageCV();
        link2_images.push_back(I6);
        I7 = TIB7->getTactileImageCV();
        link2_images.push_back(I7);
        I8 = TIB8->getTactileImageCV();
        link2_images.push_back(I8);

        cv::resize(I1, I1_resized, cv::Size(500, 500));
        cv::resize(I2, I2_resized, cv::Size(500, 500));
        cv::resize(I3, I3_resized, cv::Size(500, 500));
        cv::resize(I4, I4_resized, cv::Size(500, 500));
        cv::resize(I5, I5_resized, cv::Size(500, 500));
        cv::resize(I6, I6_resized, cv::Size(500, 500));
        cv::resize(I7, I7_resized, cv::Size(500, 500));
        cv::resize(I8, I8_resized, cv::Size(500, 500));

        cv::imshow("Tactile Image 1", I1_resized);
        cv::imshow("Tactile Image 2", I2_resized);
        cv::imshow("Tactile Image 3", I3_resized);
        cv::imshow("Tactile Image 4", I4_resized);
        cv::imshow("Tactile Image 5", I5_resized);
        cv::imshow("Tactile Image 6", I6_resized);
        cv::imshow("Tactile Image 7", I7_resized);
        cv::imshow("Tactile Image 8", I8_resized);

        // publish images
        uc1_tactile_images::msg::ImageArrayLink link1_img_msg, link2_img_msg;

        // link 1
        for (size_t i = 0; i < link1_images.size(); ++i)
        {
            link1_img_msg.images[i] = to_ros_img(link1_images[i], "tactile_link1");
        }

        // link 2
        for (size_t i = 0; i < link1_images.size(); ++i)
        {
            link2_img_msg.images[i] = to_ros_img(link2_images[i], "tactile_link2");
        }

        pub_link1->publish(link1_img_msg);
        pub_link2->publish(link2_img_msg);

        cv::waitKey(1);
    }

    u.stopRobotSkinUpdater();

    return 0;
}
