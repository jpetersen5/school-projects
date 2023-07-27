cmake_minimum_required(VERSION 3.5)
project(finalproject)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(nav2_msgs REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(lifecycle_msgs REQUIRED)
find_package(action_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(laser_geometry REQUIRED)
find_package(tf2_sensor_msgs REQUIRED)
set(PCL_DIR "/usr/lib/x86_64-linux-gnu/cmake/pcl")
find_package(PCL REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(gazebo_msgs REQUIRED)
find_package(std_msgs REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

add_library(navigator src/navigation.cpp)
add_executable(pillarbot src/finalprojectnav.cpp src/navigation.cpp)

target_include_directories(navigator
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

target_include_directories(pillarbot
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

ament_target_dependencies(navigator rclcpp geometry_msgs lifecycle_msgs rclcpp_action nav2_msgs)
ament_export_targets(navigatorlib HAS_LIBRARY_TARGET)
ament_export_dependencies(rclcpp geometry_msgs lifecycle_msgs rclcpp_action nav2_msgs)
ament_target_dependencies(pillarbot rclcpp geometry_msgs lifecycle_msgs rclcpp_action nav2_msgs nav_msgs tf2 tf2_msgs tf2_ros sensor_msgs laser_geometry tf2_sensor_msgs PCL pcl_conversions gazebo_msgs std_msgs)


install(
  DIRECTORY include/
  DESTINATION include
)

install(
  TARGETS navigator
  EXPORT navigatorlib
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
  )

install(TARGETS pillarbot DESTINATION lib/${PROJECT_NAME})


ament_package()
