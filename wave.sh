#!/bin/bash

#Setup
#roslaunch capstone_test start_meta_controller.launch

#Set speeds
rosservice call /right_shoulder_tip_controller/set_speed 0.5
rosservice call /right_elbow_controller/set_speed 0.5
rosservice call /right_shoulder_controller/set_speed 0.5
rosservice call /right_upper_arm_controller/set_speed 0.5

#Neutral 
rostopic pub -1 /right_upper_arm_controller/command std_msgs/Float64 -- 0
rostopic pub -1 /right_shoulder_controller/command std_msgs/Float64 -- 0.04290
rostopic pub -1 /right_elbow_controller/command std_msgs/Float64 -- -0.3129
rostopic pub -1 /right_shoulder_tip_controller/command std_msgs/Float64 -- 0

#Lift forearm from elbow
rostopic pub -1 /right_elbow_controller/command std_msgs/Float64 -- 1.3790
#Lift arm from shoulder
rostopic pub -1 /right_shoulder_controller/command std_msgs/Float64 -- 0.81
#Wave to one side
rostopic pub -1 /right_upper_arm_controller/command std_msgs/Float64 -- 0.6074
#Wave to the other
rostopic pub -1 /right_upper_arm_controller/command std_msgs/Float64 -- -0.8
#Wave to one side
rostopic pub -1 /right_upper_arm_controller/command std_msgs/Float64 -- 0.6074
#Wave to the other
rostopic pub -1 /right_upper_arm_controller/command std_msgs/Float64 -- -0.8

#RETURN TO ZERO
rostopic pub -1 /right_upper_arm_controller/command std_msgs/Float64 -- 0
rostopic pub -1 /right_shoulder_controller/command std_msgs/Float64 -- 0.04290
rostopic pub -1 /right_elbow_controller/command std_msgs/Float64 -- -0.3129
rostopic pub -1 /right_shoulder_tip_controller/command std_msgs/Float64 -- 0








