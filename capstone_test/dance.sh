#!/bin/bash

#Setup
#roslaunch capstone_test start_meta_controller.launch
#run bash initialize.sh before running this file to set motor speeds and zero position

#Lift forearm from elbow both arms
rostopic pub -1 /right_elbow_controller/command std_msgs/Float64 -- 1.3790
rostopic pub -1 /left_elbow_controller/command std_msgs/Float64 -- 1.3
#go higher to max on both
rostopic pub -1 /right_elbow_controller/command std_msgs/Float64 -- 1.6
rostopic pub -1 /left_elbow_controller/command std_msgs/Float64 -- 1.6
#turn arms out
rostopic pub -1 /right_shoulder_controller/command std_msgs/Float64 -- 0.81
rostopic pub -1 /left_shoulder_controller/command std_msgs/Float64 -- -1.2
#turn back in
rostopic pub -1 /right_shoulder_controller/command std_msgs/Float64 -- 0
rostopic pub -1 /left_shoulder_controller/command std_msgs/Float64 -- 0.04290

#RETURN TO Neutral
rostopic pub -1 /right_shoulder_controller/command std_msgs/Float64 -- 0.04290
rostopic pub -1 /right_elbow_controller/command std_msgs/Float64 -- -0.3129
rostopic pub -1 /left_shoulder_controller/command std_msgs/Float64 -- 0
rostopic pub -1 /left_elbow_controller/command std_msgs/Float64 -- -0.25

