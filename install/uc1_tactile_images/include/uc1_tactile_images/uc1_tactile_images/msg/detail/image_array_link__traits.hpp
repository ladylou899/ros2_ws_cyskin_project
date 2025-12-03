// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from uc1_tactile_images:msg/ImageArrayLink.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "uc1_tactile_images/msg/image_array_link.hpp"


#ifndef UC1_TACTILE_IMAGES__MSG__DETAIL__IMAGE_ARRAY_LINK__TRAITS_HPP_
#define UC1_TACTILE_IMAGES__MSG__DETAIL__IMAGE_ARRAY_LINK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "uc1_tactile_images/msg/detail/image_array_link__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'images'
#include "sensor_msgs/msg/detail/image__traits.hpp"

namespace uc1_tactile_images
{

namespace msg
{

inline void to_flow_style_yaml(
  const ImageArrayLink & msg,
  std::ostream & out)
{
  out << "{";
  // member: images
  {
    if (msg.images.size() == 0) {
      out << "images: []";
    } else {
      out << "images: [";
      size_t pending_items = msg.images.size();
      for (auto item : msg.images) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ImageArrayLink & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: images
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.images.size() == 0) {
      out << "images: []\n";
    } else {
      out << "images:\n";
      for (auto item : msg.images) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ImageArrayLink & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace uc1_tactile_images

namespace rosidl_generator_traits
{

[[deprecated("use uc1_tactile_images::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const uc1_tactile_images::msg::ImageArrayLink & msg,
  std::ostream & out, size_t indentation = 0)
{
  uc1_tactile_images::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use uc1_tactile_images::msg::to_yaml() instead")]]
inline std::string to_yaml(const uc1_tactile_images::msg::ImageArrayLink & msg)
{
  return uc1_tactile_images::msg::to_yaml(msg);
}

template<>
inline const char * data_type<uc1_tactile_images::msg::ImageArrayLink>()
{
  return "uc1_tactile_images::msg::ImageArrayLink";
}

template<>
inline const char * name<uc1_tactile_images::msg::ImageArrayLink>()
{
  return "uc1_tactile_images/msg/ImageArrayLink";
}

template<>
struct has_fixed_size<uc1_tactile_images::msg::ImageArrayLink>
  : std::integral_constant<bool, has_fixed_size<sensor_msgs::msg::Image>::value> {};

template<>
struct has_bounded_size<uc1_tactile_images::msg::ImageArrayLink>
  : std::integral_constant<bool, has_bounded_size<sensor_msgs::msg::Image>::value> {};

template<>
struct is_message<uc1_tactile_images::msg::ImageArrayLink>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // UC1_TACTILE_IMAGES__MSG__DETAIL__IMAGE_ARRAY_LINK__TRAITS_HPP_
