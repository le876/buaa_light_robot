cmake_minimum_required(VERSION 3.8)
project(buaa_rescue_robot_gui)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(buaa_rescue_robot_msgs REQUIRED)

include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(buaa_rescue_robot_gui_node
  src/main.cpp
  src/mainwindow.cpp
  src/mainwindow.h
  src/mainwindow.ui
)

target_link_libraries(buaa_rescue_robot_gui_node
  Qt5::Core
  Qt5::Gui
  Qt5::Widgets
)

ament_target_dependencies(buaa_rescue_robot_gui_node
  rclcpp
  std_msgs
  buaa_rescue_robot_msgs
)

install(TARGETS
  buaa_rescue_robot_gui_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
