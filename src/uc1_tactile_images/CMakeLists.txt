cmake_minimum_required(VERSION 3.12)

project(uc1_tactile_images)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  add_compile_options(-Wall -Wextra)
endif()

# --- define where your local lib is ---
set(ROBOSKIN_ROOT "/home/lidia/PFE/librobotskin")
set(ROBOSKIN_INC  "${ROBOSKIN_ROOT}/include")
# adjust the .so name to the real one in your build dir:
set(ROBOSKIN_SO   "${ROBOSKIN_ROOT}/build/librobotskin.so")

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(interactive_markers REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_eigen REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(pcl_msgs REQUIRED)
find_package(pcl_ros REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(urdf REQUIRED)
find_package(Doxygen)
#find_package(skin REQUIRED)
find_package(PCL REQUIRED COMPONENTS io)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)
find_package(image_transport REQUIRED)

# custom msgs
find_package(rosidl_default_generators REQUIRED)
find_package(rosidl_default_runtime REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/ImageArrayLink.msg"
  DEPENDENCIES sensor_msgs
)
ament_export_dependencies(rosidl_default_runtime)

# required for opencv functions in robotskinlib
set(ENABLE_OPENCV_SUPPORT ON CACHE BOOL "Config")
if(ENABLE_OPENCV_SUPPORT)
	add_definitions(-DOPENCV_SUPPORT=1)
	message(STATUS "OPTIONS: OPENCV support ENABLED")
else()
	add_definitions(-DOPENCV_SUPPORT=0)
	message(STATUS "OPTIONS: OPENCV support DISABLED")
endif(ENABLE_OPENCV_SUPPORT)

if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxygen)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
endif()

include_directories(
  include
  #/opt/ros/humble/include
   ${OpenCV_INCLUDE_DIRS},
  ${EIGEN3_INCLUDE_DIR}
  /home/lidia/PFE/librobotskin/include
  ${cv_bridge_INCLUDE_DIRS}
)

# link to .so file for robotskinlib
#link_directories(/home/francesco/Documents/TOOLS/librobotskin/build)

# tactile task generator
add_executable(tactile_image_publisher src/TactileImagePublisher.cpp)
target_link_libraries(tactile_image_publisher ${OpenCV_LIBRARIES} ${cv_bridge_LIBRARIES} -lpthread "${ROBOSKIN_SO}")
set_target_properties(tactile_image_publisher PROPERTIES
  BUILD_RPATH         "${ROBOSKIN_ROOT}/build"
  INSTALL_RPATH       "${ROBOSKIN_ROOT}/build"
  SKIP_BUILD_RPATH    OFF
  BUILD_WITH_INSTALL_RPATH OFF
)
ament_target_dependencies(tactile_image_publisher
rclcpp
rosidl_typesupport_cpp
geometry_msgs
sensor_msgs
PCL
pcl_conversions
std_msgs
visualization_msgs
tf2 
tf2_ros 
tf2_eigen
tf2_geometry_msgs
Eigen3
cv_bridge
image_transport
OpenCV
)
rosidl_target_interfaces(tactile_image_publisher
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

  # tactile task generator
add_executable(tactile_image_publisher_hexagon src/TactileImagePublisherHexagon.cpp)
target_link_libraries(tactile_image_publisher_hexagon ${OpenCV_LIBRARIES} ${cv_bridge_LIBRARIES} -lpthread "${ROBOSKIN_SO}")
set_target_properties(tactile_image_publisher_hexagon PROPERTIES
  BUILD_RPATH         "${ROBOSKIN_ROOT}/build"
  INSTALL_RPATH       "${ROBOSKIN_ROOT}/build"
  SKIP_BUILD_RPATH    OFF
  BUILD_WITH_INSTALL_RPATH OFF
)
ament_target_dependencies(tactile_image_publisher_hexagon
rclcpp
rosidl_typesupport_cpp
geometry_msgs
sensor_msgs
PCL
pcl_conversions
std_msgs
visualization_msgs
tf2 
tf2_ros 
tf2_eigen
tf2_geometry_msgs
Eigen3
cv_bridge
image_transport
OpenCV
)
rosidl_target_interfaces(tactile_image_publisher_hexagon
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

# CURVED PATCH  
add_executable(tactile_image_publisher_curved_gesture src/TactileImagePublisherCurvedGesture.cpp)
target_link_libraries(tactile_image_publisher_curved_gesture ${OpenCV_LIBRARIES} ${cv_bridge_LIBRARIES} -lpthread "${ROBOSKIN_SO}")
set_target_properties(tactile_image_publisher_curved_gesture PROPERTIES
  BUILD_RPATH         "${ROBOSKIN_ROOT}/build"
  INSTALL_RPATH       "${ROBOSKIN_ROOT}/build"
  SKIP_BUILD_RPATH    OFF
  BUILD_WITH_INSTALL_RPATH OFF
)
ament_target_dependencies(tactile_image_publisher_curved_gesture
rclcpp
rosidl_typesupport_cpp
geometry_msgs
sensor_msgs
PCL
pcl_conversions
std_msgs
visualization_msgs
tf2 
tf2_ros 
tf2_eigen
tf2_geometry_msgs
Eigen3
cv_bridge
image_transport
OpenCV
)
rosidl_target_interfaces(tactile_image_publisher_curved_gesture
  ${PROJECT_NAME} "rosidl_typesupport_cpp")
  


install(TARGETS
   tactile_image_publisher
   tactile_image_publisher_hexagon
   tactile_image_publisher_curved_gesture
  DESTINATION lib/${PROJECT_NAME})

# Install launch files
install(DIRECTORY
  DESTINATION share/${PROJECT_NAME}/
)

# Install robot model files
install(DIRECTORY
  resources
  DESTINATION share/${PROJECT_NAME}/
)

# Install skin network IDs
install(DIRECTORY
  skin_ids
  DESTINATION share/${PROJECT_NAME}
)

# Install models 
install(
  DIRECTORY models_onnx
  DESTINATION share/${PROJECT_NAME}
)

# Install package.xml (required for custom msgs)
install(
  FILES package.xml
  DESTINATION share/${PROJECT_NAME}
)

# Install the calibration files
install(DIRECTORY calibration_files/
  DESTINATION share/${PROJECT_NAME}/calibration_files
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
