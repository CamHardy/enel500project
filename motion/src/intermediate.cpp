#include <ros/ros.h>
#include <iostream>
#include <Python.h>
#include <robot_msgs/VisionCommand.h>

std::string command_1 = "python /home/capstone/catkin_ws/src/motion/scripts/right_arm_wave.py";
std::string command_2 = "python /home/capstone/catkin_ws/src/motion/scripts/dance.py";
std::string command_3 = "python /home/capstone/catkin_ws/src/motion/scripts/initialization.py";

std::string test_command = "python right_arm_wave.py";

uint32_t init = 0;
uint32_t wave = 1;
uint32_t dance = 2;

uint32_t commandID_one =  1035;
uint32_t commandID_two = 1100;
uint32_t commandID_three = 1400;

void movementCallBack(const robot_msgs::VisionCommand::ConstPtr& msg){
	
	//Initialization	    
	if (msg->command.command_id == init || msg->command.command_id == commandID_one)
		system(command_3.c_str());
	

	//Right Arm Wave
	else if (msg->command.command_id == wave || msg->command.command_id == commandID_two)
		system(command_1.c_str());

	//Dance
	else if (msg->command.command_id == dance || msg->command.command_id == commandID_three)
		system(command_2.c_str());
	

	/*
	 * MOTION TRACKING MODULE THAT IS NOT IN USE
	else if (msg->command.command_id == commandID_four){
		ros::NodeHandle p;
		ros::Publisher tracking_pub = p.advertise<robot_msgs::VisionCommand>("/vision_telemetry",10);
		ros::Rate pub_rate (10.0);
		tracking_pub.publish(msg);
	}*/
}

int main(int argc, char * argv[]){
	ros::init(argc, argv, "intermediate");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("/robot/vision/vision_command", 10, movementCallBack);
	ros::Rate rate (10.0);

	while(n.ok()){
		ros::spinOnce();
		rate.sleep();
	}

	return 0;
}
















