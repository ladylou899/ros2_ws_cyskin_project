# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_cyskin_acquisition_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED cyskin_acquisition_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(cyskin_acquisition_FOUND FALSE)
  elseif(NOT cyskin_acquisition_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(cyskin_acquisition_FOUND FALSE)
  endif()
  return()
endif()
set(_cyskin_acquisition_CONFIG_INCLUDED TRUE)

# output package information
if(NOT cyskin_acquisition_FIND_QUIETLY)
  message(STATUS "Found cyskin_acquisition: 0.0.1 (${cyskin_acquisition_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'cyskin_acquisition' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT cyskin_acquisition_DEPRECATED_QUIET)
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(cyskin_acquisition_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${cyskin_acquisition_DIR}/${_extra}")
endforeach()
