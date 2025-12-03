
cmake_minimum_required(VERSION 3.15)

project(cyskin_acquisition)
SET(PROGRAM_NAME cyskin_acquisition)

# Use C++17 for ROS 2 (rclcpp and modern std features)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(NOT CMAKE_CXX_FLAGS)
	set(CMAKE_CXX_FLAGS "-Wall")
else()
	string(APPEND CMAKE_CXX_FLAGS " -Wall")
endif()

#### ENABLE COMPILE OPTIONS ##############################

# Compile for the right hardware
if(WIN32)
	add_definitions(-DPCAN_SUPPORT=FALSE)
   	SET(CY_SUPPORT_PCAN false)
  	SET(CY_SUPPORT_ESDCAN true)
else()
  	add_definitions(-DPCAN_SUPPORT=TRUE)
    SET(CY_SUPPORT_PCAN true)
    SET(CY_SUPPORT_ESDCAN false)
endif()

## ENABLE HARDWARE SUPPORT
set(ENABLE_HARDWARE_SUPPORT ON CACHE BOOL "Config")
if(ENABLE_HARDWARE_SUPPORT)
	add_definitions(-DHARDWARE_SUPPORT=1)
  	message(STATUS "OPTIONS: Hardware support ENABLED")
else()
  	add_definitions(-DHARDWARE_SUPPORT=0)
  	message(STATUS "OPTIONS: Hardware support DISABLED")
	SET(CY_SUPPORT_PCAN false)
	SET(CY_SUPPORT_ESDCAN false)
endif(ENABLE_HARDWARE_SUPPORT)

## ENABLE ARM SUPPORT
set(ENABLE_ARM_SUPPORT OFF CACHE BOOL "Config")
if(ENABLE_ARM_SUPPORT)
    message(STATUS "OPTIONS: ARM support ENABLED")
else()
   	message(STATUS "OPTIONS: ARM support DISABLED")
endif(ENABLE_ARM_SUPPORT)

# Only if you are under unix
if(UNIX)
  ## ENABLE ROS SUPPORT
  	set(ENABLE_ROS_SUPPORT OFF CACHE BOOL "Config")
  	if(ENABLE_ROS_SUPPORT)
    	add_definitions(-DROS_SUPPORT=1)
    	message(STATUS "OPTIONS: ROS support ENABLED")
  	else()
    	add_definitions(-DROS_SUPPORT=0)
    	message(STATUS "OPTIONS: ROS support DISABLED")
  	endif(ENABLE_ROS_SUPPORT)

	## ENABLE ROS2 SUPPORT
	set(ENABLE_ROS2_SUPPORT ON CACHE BOOL "Config")
	if(ENABLE_ROS2_SUPPORT)
		add_definitions(-DROS2_SUPPORT=1)
		message(STATUS "OPTIONS: ROS2 support ENABLED")
	else()
		add_definitions(-DROS2_SUPPORT=0)
		message(STATUS "OPTIONS: ROS2 support DISABLED")
	endif(ENABLE_ROS2_SUPPORT)
    
    # If ROS2 support is enabled, find ROS2 packages
    if(ENABLE_ROS2_SUPPORT)
        find_package(ament_cmake REQUIRED)
        find_package(rclcpp REQUIRED)
        find_package(std_msgs REQUIRED)
    endif()
endif(UNIX)

##########################################################

# Main executable sources (explicit list)
set(MAIN_SRCS 
    src/main.cpp
    src/bash_publisher.cpp
    src/calibrator.cpp
    src/file_publisher.cpp
    src/ros_publisher.cpp
    src/shared_memory_publisher.cpp
    src/updater.cpp
    src/updater_fake.cpp
    src/updater_interface.cpp
)
add_executable(${PROGRAM_NAME} ${MAIN_SRCS})

# Add subscriber executable
if(ENABLE_ROS2_SUPPORT)
    add_executable(cyskin_subscriber 
        src/subscriber_main.cpp 
        src/cyskin_subscriber.cpp)
    
    ament_target_dependencies(cyskin_subscriber
        rclcpp
        std_msgs)
    
    target_include_directories(cyskin_subscriber PRIVATE include)
endif()

include_directories(
	include
	${CMAKE_CURRENT_SOURCE_DIR}/libs/cynetworklib/include
	${CMAKE_CURRENT_SOURCE_DIR}/libs/cybootloaderutils/include 
	${CMAKE_CURRENT_SOURCE_DIR}/st-ihb-shared 
	${CMAKE_CURRENT_SOURCE_DIR}/skin-ihb-pc-shared 
	${CMAKE_CURRENT_SOURCE_DIR}/ihb-pc-shared 
	${CMAKE_CURRENT_SOURCE_DIR}/can_helper
  )

# Set Dependencies
if(UNIX)
	if(ENABLE_ROS_SUPPORT)
		find_package(catkin REQUIRED COMPONENTS std_msgs roscpp message_runtime message_generation)
		include_directories(${catkin_INCLUDE_DIRS})
		### to be replaced with cmake cache
		include_directories( /home/ale/ros_ws/cyskin_ws/devel/include/ )
		###
		catkin_package(CATKIN_DEPENDS std_msgs roscpp)
	endif(ENABLE_ROS_SUPPORT)

	# If ROS2 support is enabled, add ament dependencies for the target
	if(ENABLE_ROS2_SUPPORT)
		# Ensure rclcpp and std_msgs are available (found earlier)
		ament_target_dependencies(${PROGRAM_NAME}
		  rclcpp
		  std_msgs
		)
	endif()

	if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 7.0)
		SET(COMPILER_VERSION 7_4)
	else()
		SET(COMPILER_VERSION 5_4)	
	endif()
	
	SET(LIB_CYBOOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/cybootloaderutils/${COMPILER_VERSION}/)
	SET(LIB_CYNET_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/cynetworklib/${COMPILER_VERSION}/)

	if(ENABLE_ARM_SUPPORT)
		SET(LIB_CYBOOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/cybootloaderutils/arm_64/)
		SET(LIB_CYNET_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/cynetworklib/arm_64/)
	endif(ENABLE_ARM_SUPPORT)
	
else() # WIN32
	SET(LIB_CYBOOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/cybootloaderutils/win/x64/)
	SET(LIB_CYNET_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/cynetworklib/win/x64/)
	SET(LIB_NTCAN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/ntcan/x64/)
endif(UNIX)

if(WIN32) # build static under windows
	target_link_libraries(
		${PROGRAM_NAME} -static
		${LIB_CYNET_DIR}/libcynetworklib.a
		${LIB_CYBOOT_DIR}/libcybootloaderutils.a
		-lpthread
	)
else()
	target_link_libraries(
			${PROGRAM_NAME}
			${LIB_CYNET_DIR}/libcynetworklib.a
			${LIB_CYBOOT_DIR}/libcybootloaderutils.a
			-lpthread
		)
endif(WIN32)

IF(${CY_SUPPORT_ESDCAN})
	target_link_libraries(${PROJECT_NAME} ${LIB_NTCAN_DIR}/ntcan.lib)
	# Do not know why but some times it must be forces, otherwise the flag will not be seen from cpp files
	target_compile_definitions(${PROJECT_NAME} PRIVATE CY_SUPPORT_ESDCAN=TRUE)
ENDIF()

IF(${CY_SUPPORT_PCAN})
	target_link_libraries(${PROJECT_NAME} -lpcan)
ENDIF()

if(UNIX)
	if(ENABLE_ROS_SUPPORT)
		target_link_libraries(${PROGRAM_NAME} ${catkin_LIBRARIES})
	endif()
endif(UNIX)

# Configurations for installation
set(TOOL_DEST ${CMAKE_INSTALL_BINDIR})
set(INCLUDE_DEST ${CMAKE_INSTALL_INCLUDEDIR}/cyskin_acquisition/include)
set(LIB_DEST ${CMAKE_INSTALL_LIBDIR}/cyskin_acquisition)
#set(THIRD_PARTY_DEST ${CMAKE_INSTALL_INCLUDEDIR}/robotskinlib/third_party)

include(GNUInstallDirs)
set(INSTALL_CMAKE_CONFIG_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/cyskin_acquisition)

target_include_directories(cyskin_acquisition 
	PUBLIC
	$<INSTALL_INTERFACE:${INCLUDE_DEST}>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

## Install for ROS2
if(ENABLE_ROS2_SUPPORT)
  # Use ament installation for ROS2
  install(TARGETS ${PROGRAM_NAME} cyskin_subscriber
    DESTINATION lib/${PROJECT_NAME})
else()
  # Use regular CMake installation for non-ROS2 builds
  install(TARGETS cyskin_acquisition 
    EXPORT cyskin_acquisitionTargets  
    LIBRARY DESTINATION ${LIB_DEST}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()

# Uninstall
if(NOT TARGET uninstall)
configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
	IMMEDIATE @ONLY
	)

add_custom_target(uninstall
	COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

if(ENABLE_ROS2_SUPPORT)
	ament_package()
endif()