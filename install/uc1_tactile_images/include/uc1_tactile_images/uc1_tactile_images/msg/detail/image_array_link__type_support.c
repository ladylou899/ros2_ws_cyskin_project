// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from uc1_tactile_images:msg/ImageArrayLink.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "uc1_tactile_images/msg/detail/image_array_link__rosidl_typesupport_introspection_c.h"
#include "uc1_tactile_images/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "uc1_tactile_images/msg/detail/image_array_link__functions.h"
#include "uc1_tactile_images/msg/detail/image_array_link__struct.h"


// Include directives for member types
// Member `images`
#include "sensor_msgs/msg/image.h"
// Member `images`
#include "sensor_msgs/msg/detail/image__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__ImageArrayLink_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  uc1_tactile_images__msg__ImageArrayLink__init(message_memory);
}

void uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__ImageArrayLink_fini_function(void * message_memory)
{
  uc1_tactile_images__msg__ImageArrayLink__fini(message_memory);
}

size_t uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__size_function__ImageArrayLink__images(
  const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__get_const_function__ImageArrayLink__images(
  const void * untyped_member, size_t index)
{
  const sensor_msgs__msg__Image * member =
    (const sensor_msgs__msg__Image *)(untyped_member);
  return &member[index];
}

void * uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__get_function__ImageArrayLink__images(
  void * untyped_member, size_t index)
{
  sensor_msgs__msg__Image * member =
    (sensor_msgs__msg__Image *)(untyped_member);
  return &member[index];
}

void uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__fetch_function__ImageArrayLink__images(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const sensor_msgs__msg__Image * item =
    ((const sensor_msgs__msg__Image *)
    uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__get_const_function__ImageArrayLink__images(untyped_member, index));
  sensor_msgs__msg__Image * value =
    (sensor_msgs__msg__Image *)(untyped_value);
  *value = *item;
}

void uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__assign_function__ImageArrayLink__images(
  void * untyped_member, size_t index, const void * untyped_value)
{
  sensor_msgs__msg__Image * item =
    ((sensor_msgs__msg__Image *)
    uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__get_function__ImageArrayLink__images(untyped_member, index));
  const sensor_msgs__msg__Image * value =
    (const sensor_msgs__msg__Image *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__ImageArrayLink_message_member_array[1] = {
  {
    "images",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(uc1_tactile_images__msg__ImageArrayLink, images),  // bytes offset in struct
    NULL,  // default value
    uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__size_function__ImageArrayLink__images,  // size() function pointer
    uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__get_const_function__ImageArrayLink__images,  // get_const(index) function pointer
    uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__get_function__ImageArrayLink__images,  // get(index) function pointer
    uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__fetch_function__ImageArrayLink__images,  // fetch(index, &value) function pointer
    uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__assign_function__ImageArrayLink__images,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__ImageArrayLink_message_members = {
  "uc1_tactile_images__msg",  // message namespace
  "ImageArrayLink",  // message name
  1,  // number of fields
  sizeof(uc1_tactile_images__msg__ImageArrayLink),
  false,  // has_any_key_member_
  uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__ImageArrayLink_message_member_array,  // message members
  uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__ImageArrayLink_init_function,  // function to initialize message memory (memory has to be allocated)
  uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__ImageArrayLink_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__ImageArrayLink_message_type_support_handle = {
  0,
  &uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__ImageArrayLink_message_members,
  get_message_typesupport_handle_function,
  &uc1_tactile_images__msg__ImageArrayLink__get_type_hash,
  &uc1_tactile_images__msg__ImageArrayLink__get_type_description,
  &uc1_tactile_images__msg__ImageArrayLink__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_uc1_tactile_images
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, uc1_tactile_images, msg, ImageArrayLink)() {
  uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__ImageArrayLink_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sensor_msgs, msg, Image)();
  if (!uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__ImageArrayLink_message_type_support_handle.typesupport_identifier) {
    uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__ImageArrayLink_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &uc1_tactile_images__msg__ImageArrayLink__rosidl_typesupport_introspection_c__ImageArrayLink_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
