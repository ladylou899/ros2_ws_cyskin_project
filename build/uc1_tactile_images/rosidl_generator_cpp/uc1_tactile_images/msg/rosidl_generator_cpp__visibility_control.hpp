// generated from rosidl_generator_cpp/resource/rosidl_generator_cpp__visibility_control.hpp.in
// generated code does not contain a copyright notice

#ifndef UC1_TACTILE_IMAGES__MSG__ROSIDL_GENERATOR_CPP__VISIBILITY_CONTROL_HPP_
#define UC1_TACTILE_IMAGES__MSG__ROSIDL_GENERATOR_CPP__VISIBILITY_CONTROL_HPP_

#ifdef __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_GENERATOR_CPP_EXPORT_uc1_tactile_images __attribute__ ((dllexport))
    #define ROSIDL_GENERATOR_CPP_IMPORT_uc1_tactile_images __attribute__ ((dllimport))
  #else
    #define ROSIDL_GENERATOR_CPP_EXPORT_uc1_tactile_images __declspec(dllexport)
    #define ROSIDL_GENERATOR_CPP_IMPORT_uc1_tactile_images __declspec(dllimport)
  #endif
  #ifdef ROSIDL_GENERATOR_CPP_BUILDING_DLL_uc1_tactile_images
    #define ROSIDL_GENERATOR_CPP_PUBLIC_uc1_tactile_images ROSIDL_GENERATOR_CPP_EXPORT_uc1_tactile_images
  #else
    #define ROSIDL_GENERATOR_CPP_PUBLIC_uc1_tactile_images ROSIDL_GENERATOR_CPP_IMPORT_uc1_tactile_images
  #endif
#else
  #define ROSIDL_GENERATOR_CPP_EXPORT_uc1_tactile_images __attribute__ ((visibility("default")))
  #define ROSIDL_GENERATOR_CPP_IMPORT_uc1_tactile_images
  #if __GNUC__ >= 4
    #define ROSIDL_GENERATOR_CPP_PUBLIC_uc1_tactile_images __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_GENERATOR_CPP_PUBLIC_uc1_tactile_images
  #endif
#endif

#ifdef __cplusplus
}
#endif

#endif  // UC1_TACTILE_IMAGES__MSG__ROSIDL_GENERATOR_CPP__VISIBILITY_CONTROL_HPP_
