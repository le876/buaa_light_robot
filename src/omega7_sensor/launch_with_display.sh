#!/bin/bash

# 设置显示相关的环境变量
export DISPLAY=:0
export QT_QPA_PLATFORM=offscreen
export LIBGL_ALWAYS_INDIRECT=1
export XDG_RUNTIME_DIR=/tmp/runtime-rescue-robot

# 确保运行时目录存在
mkdir -p /tmp/runtime-rescue-robot
chmod 700 /tmp/runtime-rescue-robot

# 启动ROS2节点
ros2 launch buaa_rescue_robot_msgs control_by_keyboard.launch.py 