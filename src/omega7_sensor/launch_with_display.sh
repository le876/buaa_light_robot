#!/bin/bash

# ������ʾ��صĻ�������
export DISPLAY=:0
export QT_QPA_PLATFORM=offscreen
export LIBGL_ALWAYS_INDIRECT=1
export XDG_RUNTIME_DIR=/tmp/runtime-rescue-robot

# ȷ������ʱĿ¼����
mkdir -p /tmp/runtime-rescue-robot
chmod 700 /tmp/runtime-rescue-robot

# ����ROS2�ڵ�
ros2 launch buaa_rescue_robot_msgs control_by_keyboard.launch.py 