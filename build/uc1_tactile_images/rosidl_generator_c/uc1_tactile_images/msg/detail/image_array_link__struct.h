// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uc1_tactile_images:msg/ImageArrayLink.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "uc1_tactile_images/msg/image_array_link.h"


#ifndef UC1_TACTILE_IMAGES__MSG__DETAIL__IMAGE_ARRAY_LINK__STRUCT_H_
#define UC1_TACTILE_IMAGES__MSG__DETAIL__IMAGE_ARRAY_LINK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'images'
#include "sensor_msgs/msg/detail/image__struct.h"

/// Struct defined in msg/ImageArrayLink in the package uc1_tactile_images.
typedef struct uc1_tactile_images__msg__ImageArrayLink
{
  sensor_msgs__msg__Image images[4];
} uc1_tactile_images__msg__ImageArrayLink;

// Struct for a sequence of uc1_tactile_images__msg__ImageArrayLink.
typedef struct uc1_tactile_images__msg__ImageArrayLink__Sequence
{
  uc1_tactile_images__msg__ImageArrayLink * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uc1_tactile_images__msg__ImageArrayLink__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UC1_TACTILE_IMAGES__MSG__DETAIL__IMAGE_ARRAY_LINK__STRUCT_H_
