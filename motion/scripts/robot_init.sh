#!/bin/bash
export PATH="/opt/ros/kinetic/bin:/home/capstone/bin:/home/capstone/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"
export LD_LIBRARY_PATH="/home/capstone/my_workspace/devel/lib:/home/capstone/catkin_ws/devel/lib:/opt/ros/kinetic/lib"
export PYTHONPATH="/home/capstone/my_workspace/devel/lib/python2.7/dist-packages:/home/capstone/catkin_ws/devel/lib/python2.7/dist-packages:/opt/ros/kinetic/lib/python2.7/dist-packages"
export ROS_ROOT="/opt/ros/kinetic/share/ros"
export ROS_PACKAGE_PATH="/home/capstone/my_workspace/src:/home/capstone/catkin_ws/src:/opt/ros/kinetic/share"
export PKG_CONFIG_PATH="/home/capstone/my_workspace/devel/lib/pkgconfig:/home/capstone/catkin_ws/devel/lib/pkgconfig:/opt/ros/kinetic/lib/pkgconfig"
export CMAKE_PREFIX_PATH="/home/capstone/my_workspace/devel:/home/capstone/catkin_ws/devel:/opt/ros/kinetic"
export ROS_ETC_DIR="/opt/ros/kinetic/etc/ros"
export ROS_MASTER_URI="http://localhost:11311"
export ROSLISP_PACKAGE_DIRECTORIES=/home/capstone/my_workspace/devel/share/common-lisp:/home/capstone/catkin_ws/devel/share/common-lisp
export ROS_DISTRO=kinetic


echo "Robot starting..." >> "/home/capstone/launch.log"
"/opt/ros/kinetic/bin/roslaunch" "motion" "start_meta_controller.launch" 2>&1 >> "/home/capstone/launch.log" &
echo "Robot step 2" >> "/home/capstone/launch.log"
sleep 3
"/opt/ros/kinetic/bin/roslaunch" "motion" "controller_manager.launch" &
echo "Robot step 3" >> "/home/capstone/launch.log"
"/usr/bin/python" "/home/capstone/catkin_ws/src/motion/scripts/initialization.py" &
wait
