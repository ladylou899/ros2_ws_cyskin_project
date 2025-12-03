// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from uc1_tactile_images:msg/ImageArrayLink.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "uc1_tactile_images/msg/detail/image_array_link__functions.h"
#include "uc1_tactile_images/msg/detail/image_array_link__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace uc1_tactile_images
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void ImageArrayLink_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) uc1_tactile_images::msg::ImageArrayLink(_init);
}

void ImageArrayLink_fini_function(void * message_memory)
{
  auto typed_message = static_cast<uc1_tactile_images::msg::ImageArrayLink *>(message_memory);
  typed_message->~ImageArrayLink();
}

size_t size_function__ImageArrayLink__images(const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * get_const_function__ImageArrayLink__images(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<sensor_msgs::msg::Image, 4> *>(untyped_member);
  return &member[index];
}

void * get_function__ImageArrayLink__images(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<sensor_msgs::msg::Image, 4> *>(untyped_member);
  return &member[index];
}

void fetch_function__ImageArrayLink__images(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const sensor_msgs::msg::Image *>(
    get_const_function__ImageArrayLink__images(untyped_member, index));
  auto & value = *reinterpret_cast<sensor_msgs::msg::Image *>(untyped_value);
  value = item;
}

void assign_function__ImageArrayLink__images(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<sensor_msgs::msg::Image *>(
    get_function__ImageArrayLink__images(untyped_member, index));
  const auto & value = *reinterpret_cast<const sensor_msgs::msg::Image *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ImageArrayLink_message_member_array[1] = {
  {
    "images",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<sensor_msgs::msg::Image>(),  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(uc1_tactile_images::msg::ImageArrayLink, images),  // bytes offset in struct
    nullptr,  // default value
    size_function__ImageArrayLink__images,  // size() function pointer
    get_const_function__ImageArrayLink__images,  // get_const(index) function pointer
    get_function__ImageArrayLink__images,  // get(index) function pointer
    fetch_function__ImageArrayLink__images,  // fetch(index, &value) function pointer
    assign_function__ImageArrayLink__images,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ImageArrayLink_message_members = {
  "uc1_tactile_images::msg",  // message namespace
  "ImageArrayLink",  // message name
  1,  // number of fields
  sizeof(uc1_tactile_images::msg::ImageArrayLink),
  false,  // has_any_key_member_
  ImageArrayLink_message_member_array,  // message members
  ImageArrayLink_init_function,  // function to initialize message memory (memory has to be allocated)
  ImageArrayLink_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ImageArrayLink_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ImageArrayLink_message_members,
  get_message_typesupport_handle_function,
  &uc1_tactile_images__msg__ImageArrayLink__get_type_hash,
  &uc1_tactile_images__msg__ImageArrayLink__get_type_description,
  &uc1_tactile_images__msg__ImageArrayLink__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace uc1_tactile_images


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<uc1_tactile_images::msg::ImageArrayLink>()
{
  return &::uc1_tactile_images::msg::rosidl_typesupport_introspection_cpp::ImageArrayLink_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, uc1_tactile_images, msg, ImageArrayLink)() {
  return &::uc1_tactile_images::msg::rosidl_typesupport_introspection_cpp::ImageArrayLink_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
