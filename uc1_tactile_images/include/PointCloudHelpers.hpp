#include <pcl/point_types.h>
#include <pcl/common/common_headers.h>
#include <pcl/common/transforms.h>
#include <pcl/io/obj_io.h>
#include <pcl/io/ply_io.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/io/file_io.h>
#include <pcl/conversions.h>
#include <pcl/filters/random_sample.h>
#include <pcl/filters/uniform_sampling.h>
#include <pcl/filters/statistical_outlier_removal.h>
// eigen
#include <Eigen/Core>
#include <Eigen/Dense>
//tf2
#include <geometry_msgs/msg/point_stamped.hpp>
#include <geometry_msgs/msg/vector3_stamped.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2_eigen/tf2_eigen.hpp>


// add static offsets for mismatch between tf and mesh origin
void linkTfOffset(size_t index, Eigen::Matrix4d &tf_eigen)
{
  double x, y, z;
  double yaw, roll, pitch;
  Eigen::Matrix3d R_yaw, R_roll, R_pitch;
  switch (index)
  {
  // base link inertia
  case 0:
  {
    x = 0;
    y = 0;
    z = 0;

    Eigen::Matrix3d rotation = Eigen::Matrix3d::Identity();

    tf_eigen.block<3, 3>(0, 0) = rotation;
    tf_eigen(0, 3) = x;
    tf_eigen(1, 3) = y;
    tf_eigen(2, 3) = z;
    break;
  }

  // shoulder link
  case 1:
  {
    x = 0;
    y = 0;
    z = 0;

    yaw = M_PI;
    R_yaw = Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ()).toRotationMatrix();
    Eigen::Matrix3d rotation = R_yaw;

    tf_eigen.block<3, 3>(0, 0) = rotation;
    tf_eigen(0, 3) = x;
    tf_eigen(1, 3) = y;
    tf_eigen(2, 3) = z;
    break;
  }

  // upper arm link
  case 2:
  {
    x = 0;
    y = 0;
    z = 0.1762;

    roll = -M_PI / 2;
    yaw = roll;
    R_roll = Eigen::AngleAxisd(roll, Eigen::Vector3d::UnitY()).toRotationMatrix();
    R_yaw = Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ()).toRotationMatrix();
    Eigen::Matrix3d rotation = R_roll * R_yaw;

    tf_eigen.block<3, 3>(0, 0) = rotation;
    tf_eigen(0, 3) = x;
    tf_eigen(1, 3) = y;
    tf_eigen(2, 3) = z;
    break;
  }

  // forearm link
  case 3:
  {
    x = 0;
    y = 0;
    z = 0.0393;

    roll = -M_PI / 2;
    yaw = roll;
    R_roll = Eigen::AngleAxisd(roll, Eigen::Vector3d::UnitY()).toRotationMatrix();
    R_yaw = Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ()).toRotationMatrix();
    Eigen::Matrix3d rotation = R_roll * R_yaw;

    tf_eigen.block<3, 3>(0, 0) = rotation;
    tf_eigen(0, 3) = x;
    tf_eigen(1, 3) = y;
    tf_eigen(2, 3) = z;
    break;
  }

  // wrist 1 link
  case 4:
  {
    x = 0;
    y = 0;
    z = -0.135;

    roll = M_PI / 2;

    R_roll = Eigen::AngleAxisd(roll, Eigen::Vector3d::UnitX()).toRotationMatrix();

    //Eigen::Matrix3d rotation = Eigen::Matrix3d::Identity();
    Eigen::Matrix3d rotation = R_roll;
    tf_eigen.block<3, 3>(0, 0) = rotation;
    tf_eigen(0, 3) = x;
    tf_eigen(1, 3) = y;
    tf_eigen(2, 3) = z;
    break;
  }

  // wrist 2 link
  case 5:
  {
    x = 0;
    y = 0;
    z = -0.12;

    Eigen::Matrix3d rotation = Eigen::Matrix3d::Identity();

    tf_eigen.block<3, 3>(0, 0) = rotation;
    tf_eigen(0, 3) = x;
    tf_eigen(1, 3) = y;
    tf_eigen(2, 3) = z;
    break;
  }

  // wrist 3 ( tool 0 tf) link
  case 6:
  {
    x = 0;
    y = 0;
    z = -0.1168;

    yaw = M_PI / 2;
    R_yaw = Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ()).toRotationMatrix();
    Eigen::Matrix3d rotation = R_yaw;

    roll = M_PI / 2;
    yaw = roll;
    R_roll = Eigen::AngleAxisd(roll, Eigen::Vector3d::UnitY()).toRotationMatrix();
    R_yaw = Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ()).toRotationMatrix();
    rotation *= R_roll * R_yaw;

    tf_eigen.block<3, 3>(0, 0) = rotation;
    tf_eigen(0, 3) = x;
    tf_eigen(1, 3) = y;
    tf_eigen(2, 3) = z;
    break;
  }

  default:
    std::cout << "Invalid index for transformation!" << std::endl;
  }
}


void applyCloudTransformation(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, const Eigen::Matrix4d &transform_double)
{
  // Convert Eigen::Matrix4d to Eigen::Matrix4f (needed for pcl built in function)
  Eigen::Matrix4f transform_float = transform_double.cast<float>();
  pcl::transformPointCloud(*cloud, *cloud, transform_float);
}

void removeOutliers(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{
  pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
  sor.setInputCloud(cloud);
  sor.setMeanK(20);              // neighbors 
  sor.setStddevMulThresh(1.0);   // std threshold
  sor.filter(*cloud);            // always update the same cloud
}

void removeIntersectingCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,
                          const pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud,
                          double proximity_threshold)
{
  // Build a kd-tree for the target cloud (e.g. robot model)
  pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
  kdtree.setInputCloud(target_cloud);

  // Remove points from 'cloud' if their nearest neighbor in 'target_cloud'
  // is closer than the specified threshold.
  auto new_end = std::remove_if(cloud->points.begin(), cloud->points.end(),
    [&](const pcl::PointXYZ &pt) {
      std::vector<int> indices(1);
      std::vector<float> sqr_dists(1);
      if (kdtree.nearestKSearch(pt, 1, indices, sqr_dists) > 0) {
        return std::sqrt(sqr_dists[0]) < proximity_threshold;
      }
      return false;
    });
  cloud->points.erase(new_end, cloud->points.end());
  cloud->width = static_cast<uint32_t>(cloud->points.size());
  cloud->height = 1;
  cloud->is_dense = true;
}

void cropBoundingBox(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, const Eigen::Matrix4f &bbox_transform)
{
  pcl::CropBox<pcl::PointXYZ> crop;
  crop.setInputCloud(cloud);
  Eigen::Vector4f min_pt(-1.0f, -1.0f, -1.0f, 1.0f);
  Eigen::Vector4f max_pt( 1.0f,  1.0f,  1.0f, 1.0f);
  crop.setMin(min_pt);
  crop.setMax(max_pt);
  Eigen::Affine3f affine_transform(bbox_transform);
  crop.setTransform(affine_transform);
  crop.filter(*cloud);  
}


/*
bool transform_point_and_force(tf2_ros::Buffer& buffer,
                                      const std::string& target_frame,
                                      const std::string& source_frame,
                                      const Eigen::Vector3d& point_in_source,
                                      const Eigen::Vector3d& force_in_source,
                                      Eigen::Vector3d& point_in_target,
                                      Eigen::Vector3d& force_in_target,
                                      const std::chrono::nanoseconds timeout = std::chrono::milliseconds(200))
{
  try {
    // lookup latest transform: T_target_source
    const auto T_target_source =
        buffer.lookupTransform(target_frame, source_frame, tf2::TimePointZero,
                               tf2::durationFromSec(std::chrono::duration<double>(timeout).count()));

    // transform task point
    geometry_msgs::msg::PointStamped p_src, p_tgt;
    p_src.header.frame_id = source_frame;
    p_src.point = tf2::toMsg(point_in_source);
    tf2::doTransform(p_src, p_tgt, T_target_source);
    point_in_target = tf2::fromMsg(p_tgt.point);

    // transform task vector
    geometry_msgs::msg::Vector3Stamped f_src, f_tgt;
    f_src.header.frame_id = source_frame;
    f_src.vector = tf2::toMsg(force_in_source);
    tf2::doTransform(f_src, f_tgt, T_target_source);
    force_in_target = tf2::fromMsg(f_tgt.vector);

    return true;
  } catch (const tf2::TransformException& ex) {

    return false;
  }
}*/
