// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from uc1_tactile_images:msg/ImageArrayLink.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "uc1_tactile_images/msg/image_array_link.hpp"


#ifndef UC1_TACTILE_IMAGES__MSG__DETAIL__IMAGE_ARRAY_LINK__STRUCT_HPP_
#define UC1_TACTILE_IMAGES__MSG__DETAIL__IMAGE_ARRAY_LINK__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'images'
#include "sensor_msgs/msg/detail/image__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__uc1_tactile_images__msg__ImageArrayLink __attribute__((deprecated))
#else
# define DEPRECATED__uc1_tactile_images__msg__ImageArrayLink __declspec(deprecated)
#endif

namespace uc1_tactile_images
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ImageArrayLink_
{
  using Type = ImageArrayLink_<ContainerAllocator>;

  explicit ImageArrayLink_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->images.fill(sensor_msgs::msg::Image_<ContainerAllocator>{_init});
    }
  }

  explicit ImageArrayLink_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : images(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->images.fill(sensor_msgs::msg::Image_<ContainerAllocator>{_alloc, _init});
    }
  }

  // field types and members
  using _images_type =
    std::array<sensor_msgs::msg::Image_<ContainerAllocator>, 4>;
  _images_type images;

  // setters for named parameter idiom
  Type & set__images(
    const std::array<sensor_msgs::msg::Image_<ContainerAllocator>, 4> & _arg)
  {
    this->images = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    uc1_tactile_images::msg::ImageArrayLink_<ContainerAllocator> *;
  using ConstRawPtr =
    const uc1_tactile_images::msg::ImageArrayLink_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<uc1_tactile_images::msg::ImageArrayLink_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<uc1_tactile_images::msg::ImageArrayLink_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      uc1_tactile_images::msg::ImageArrayLink_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<uc1_tactile_images::msg::ImageArrayLink_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      uc1_tactile_images::msg::ImageArrayLink_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<uc1_tactile_images::msg::ImageArrayLink_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<uc1_tactile_images::msg::ImageArrayLink_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<uc1_tactile_images::msg::ImageArrayLink_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__uc1_tactile_images__msg__ImageArrayLink
    std::shared_ptr<uc1_tactile_images::msg::ImageArrayLink_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__uc1_tactile_images__msg__ImageArrayLink
    std::shared_ptr<uc1_tactile_images::msg::ImageArrayLink_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ImageArrayLink_ & other) const
  {
    if (this->images != other.images) {
      return false;
    }
    return true;
  }
  bool operator!=(const ImageArrayLink_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ImageArrayLink_

// alias to use template instance with default allocator
using ImageArrayLink =
  uc1_tactile_images::msg::ImageArrayLink_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace uc1_tactile_images

#endif  // UC1_TACTILE_IMAGES__MSG__DETAIL__IMAGE_ARRAY_LINK__STRUCT_HPP_
