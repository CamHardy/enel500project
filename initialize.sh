#!/bin/bash

#Setup
#roslaunch capstone_test start_meta_controller.launch
#bash dance.sh

#Set speeds for all 10 motors in use
rosservice call /right_shoulder_tip_controller/set_speed 0.5
rosservice call /right_elbow_controller/set_speed 0.5
rosservice call /right_shoulder_controller/set_speed 0.5
rosservice call /right_upper_arm_controller/set_speed 0.5
rosservice call /left_shoulder_tip_controller/set_speed 0.5
rosservice call /left_elbow_controller/set_speed 0.5
rosservice call /left_shoulder_controller/set_speed 0.5
rosservice call /left_upper_arm_controller/set_speed 0.5
rosservice call /neck_controller/set_speed 0.5
rosservice call /head_controller/set_speed 0.5

#Neutral 
rostopic pub -1 /right_upper_arm_controller/command std_msgs/Float64 -- 0
rostopic pub -1 /right_shoulder_controller/command std_msgs/Float64 -- 0.04290
rostopic pub -1 /right_elbow_controller/command std_msgs/Float64 -- -0.3129
rostopic pub -1 /right_shoulder_tip_controller/command std_msgs/Float64 -- 0
rostopic pub -1 /left_upper_arm_controller/command std_msgs/Float64 -- 0
rostopic pub -1 /left_shoulder_controller/command std_msgs/Float64 -- 0
rostopic pub -1 /left_elbow_controller/command std_msgs/Float64 -- -0.25
rostopic pub -1 /left_shoulder_tip_controller/command std_msgs/Float64 -- 2.8
rostopic pub -1 /neck_controller/command std_msgs/Float64 -- 1.57
rostopic pub -1 /head_controller/command std_msgs/Float64 -- 6.28