// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from uc1_tactile_images:msg/ImageArrayLink.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "uc1_tactile_images/msg/image_array_link.hpp"


#ifndef UC1_TACTILE_IMAGES__MSG__DETAIL__IMAGE_ARRAY_LINK__BUILDER_HPP_
#define UC1_TACTILE_IMAGES__MSG__DETAIL__IMAGE_ARRAY_LINK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "uc1_tactile_images/msg/detail/image_array_link__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace uc1_tactile_images
{

namespace msg
{

namespace builder
{

class Init_ImageArrayLink_images
{
public:
  Init_ImageArrayLink_images()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::uc1_tactile_images::msg::ImageArrayLink images(::uc1_tactile_images::msg::ImageArrayLink::_images_type arg)
  {
    msg_.images = std::move(arg);
    return std::move(msg_);
  }

private:
  ::uc1_tactile_images::msg::ImageArrayLink msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::uc1_tactile_images::msg::ImageArrayLink>()
{
  return uc1_tactile_images::msg::builder::Init_ImageArrayLink_images();
}

}  // namespace uc1_tactile_images

#endif  // UC1_TACTILE_IMAGES__MSG__DETAIL__IMAGE_ARRAY_LINK__BUILDER_HPP_
