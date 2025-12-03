// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from uc1_tactile_images:msg/ImageArrayLink.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "uc1_tactile_images/msg/image_array_link.h"


#ifndef UC1_TACTILE_IMAGES__MSG__DETAIL__IMAGE_ARRAY_LINK__FUNCTIONS_H_
#define UC1_TACTILE_IMAGES__MSG__DETAIL__IMAGE_ARRAY_LINK__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"
#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "uc1_tactile_images/msg/rosidl_generator_c__visibility_control.h"

#include "uc1_tactile_images/msg/detail/image_array_link__struct.h"

/// Initialize msg/ImageArrayLink message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * uc1_tactile_images__msg__ImageArrayLink
 * )) before or use
 * uc1_tactile_images__msg__ImageArrayLink__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_tactile_images
bool
uc1_tactile_images__msg__ImageArrayLink__init(uc1_tactile_images__msg__ImageArrayLink * msg);

/// Finalize msg/ImageArrayLink message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_tactile_images
void
uc1_tactile_images__msg__ImageArrayLink__fini(uc1_tactile_images__msg__ImageArrayLink * msg);

/// Create msg/ImageArrayLink message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * uc1_tactile_images__msg__ImageArrayLink__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_tactile_images
uc1_tactile_images__msg__ImageArrayLink *
uc1_tactile_images__msg__ImageArrayLink__create(void);

/// Destroy msg/ImageArrayLink message.
/**
 * It calls
 * uc1_tactile_images__msg__ImageArrayLink__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_tactile_images
void
uc1_tactile_images__msg__ImageArrayLink__destroy(uc1_tactile_images__msg__ImageArrayLink * msg);

/// Check for msg/ImageArrayLink message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_tactile_images
bool
uc1_tactile_images__msg__ImageArrayLink__are_equal(const uc1_tactile_images__msg__ImageArrayLink * lhs, const uc1_tactile_images__msg__ImageArrayLink * rhs);

/// Copy a msg/ImageArrayLink message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_tactile_images
bool
uc1_tactile_images__msg__ImageArrayLink__copy(
  const uc1_tactile_images__msg__ImageArrayLink * input,
  uc1_tactile_images__msg__ImageArrayLink * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_uc1_tactile_images
const rosidl_type_hash_t *
uc1_tactile_images__msg__ImageArrayLink__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_uc1_tactile_images
const rosidl_runtime_c__type_description__TypeDescription *
uc1_tactile_images__msg__ImageArrayLink__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_uc1_tactile_images
const rosidl_runtime_c__type_description__TypeSource *
uc1_tactile_images__msg__ImageArrayLink__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_uc1_tactile_images
const rosidl_runtime_c__type_description__TypeSource__Sequence *
uc1_tactile_images__msg__ImageArrayLink__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/ImageArrayLink messages.
/**
 * It allocates the memory for the number of elements and calls
 * uc1_tactile_images__msg__ImageArrayLink__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_tactile_images
bool
uc1_tactile_images__msg__ImageArrayLink__Sequence__init(uc1_tactile_images__msg__ImageArrayLink__Sequence * array, size_t size);

/// Finalize array of msg/ImageArrayLink messages.
/**
 * It calls
 * uc1_tactile_images__msg__ImageArrayLink__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_tactile_images
void
uc1_tactile_images__msg__ImageArrayLink__Sequence__fini(uc1_tactile_images__msg__ImageArrayLink__Sequence * array);

/// Create array of msg/ImageArrayLink messages.
/**
 * It allocates the memory for the array and calls
 * uc1_tactile_images__msg__ImageArrayLink__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_tactile_images
uc1_tactile_images__msg__ImageArrayLink__Sequence *
uc1_tactile_images__msg__ImageArrayLink__Sequence__create(size_t size);

/// Destroy array of msg/ImageArrayLink messages.
/**
 * It calls
 * uc1_tactile_images__msg__ImageArrayLink__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_tactile_images
void
uc1_tactile_images__msg__ImageArrayLink__Sequence__destroy(uc1_tactile_images__msg__ImageArrayLink__Sequence * array);

/// Check for msg/ImageArrayLink message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_tactile_images
bool
uc1_tactile_images__msg__ImageArrayLink__Sequence__are_equal(const uc1_tactile_images__msg__ImageArrayLink__Sequence * lhs, const uc1_tactile_images__msg__ImageArrayLink__Sequence * rhs);

/// Copy an array of msg/ImageArrayLink messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_tactile_images
bool
uc1_tactile_images__msg__ImageArrayLink__Sequence__copy(
  const uc1_tactile_images__msg__ImageArrayLink__Sequence * input,
  uc1_tactile_images__msg__ImageArrayLink__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // UC1_TACTILE_IMAGES__MSG__DETAIL__IMAGE_ARRAY_LINK__FUNCTIONS_H_
