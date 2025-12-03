// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from uc1_tactile_images:msg/ImageArrayLink.idl
// generated code does not contain a copyright notice
#ifndef UC1_TACTILE_IMAGES__MSG__DETAIL__IMAGE_ARRAY_LINK__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define UC1_TACTILE_IMAGES__MSG__DETAIL__IMAGE_ARRAY_LINK__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "uc1_tactile_images/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "uc1_tactile_images/msg/detail/image_array_link__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_uc1_tactile_images
bool cdr_serialize_uc1_tactile_images__msg__ImageArrayLink(
  const uc1_tactile_images__msg__ImageArrayLink * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_uc1_tactile_images
bool cdr_deserialize_uc1_tactile_images__msg__ImageArrayLink(
  eprosima::fastcdr::Cdr &,
  uc1_tactile_images__msg__ImageArrayLink * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_uc1_tactile_images
size_t get_serialized_size_uc1_tactile_images__msg__ImageArrayLink(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_uc1_tactile_images
size_t max_serialized_size_uc1_tactile_images__msg__ImageArrayLink(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_uc1_tactile_images
bool cdr_serialize_key_uc1_tactile_images__msg__ImageArrayLink(
  const uc1_tactile_images__msg__ImageArrayLink * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_uc1_tactile_images
size_t get_serialized_size_key_uc1_tactile_images__msg__ImageArrayLink(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_uc1_tactile_images
size_t max_serialized_size_key_uc1_tactile_images__msg__ImageArrayLink(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_uc1_tactile_images
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, uc1_tactile_images, msg, ImageArrayLink)();

#ifdef __cplusplus
}
#endif

#endif  // UC1_TACTILE_IMAGES__MSG__DETAIL__IMAGE_ARRAY_LINK__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
