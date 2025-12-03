// eigen
#include <Eigen/Core>
#include <Eigen/Dense>
//tf2
#include <geometry_msgs/msg/point_stamped.hpp>
#include <geometry_msgs/msg/vector3_stamped.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2_eigen/tf2_eigen.hpp>

inline bool lookup_eigen_transform(tf2_ros::Buffer& buffer,
                                   const std::string& target_frame,
                                   const std::string& source_frame,
                                   Eigen::Isometry3d& T_target_source,
                                   std::chrono::nanoseconds timeout = std::chrono::milliseconds(200))
{
    if (!buffer.canTransform(target_frame, source_frame, tf2::TimePointZero)) {
    return false;
  }
  try {
    const auto ts = buffer.lookupTransform(target_frame, source_frame, tf2::TimePointZero);
    T_target_source = tf2::transformToEigen(ts);
    return true;
  } catch (const tf2::TransformException&) {
    std::cout << "No tf available" << std::endl;
    return false;
  }
}

inline void apply_point_and_force(const Eigen::Isometry3d& T_target_source,
                                  const Eigen::Vector3d& point_in_source,
                                  const Eigen::Vector3d& force_in_source,
                                  Eigen::Vector3d& point_in_target,
                                  Eigen::Vector3d& force_in_target)
{
  const Eigen::Matrix3d& R = T_target_source.linear();
  const Eigen::Vector3d& t = T_target_source.translation();
  point_in_target = R * point_in_source + t;
  force_in_target = R * force_in_source; 
}

inline bool transform_point_and_force_eigen(tf2_ros::Buffer& buffer,
                                            const std::string& target_frame,
                                            const std::string& source_frame,
                                            const Eigen::Vector3d& point_in_source,
                                            const Eigen::Vector3d& force_in_source,
                                            Eigen::Vector3d& point_in_target,
                                            Eigen::Vector3d& force_in_target,
                                            std::chrono::nanoseconds timeout = std::chrono::milliseconds(200))
{
  Eigen::Isometry3d T;
  if (!lookup_eigen_transform(buffer, target_frame, source_frame, T, timeout)) return false;
  apply_point_and_force(T, point_in_source, force_in_source, point_in_target, force_in_target);
  return true;
}