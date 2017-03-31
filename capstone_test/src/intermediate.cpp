#include <ros/ros.h>
#include <iostream>
#include <Python.h>
#include <capstone_test/VisionCommand.h>

std::string command_1 = "python /home/capstone/catkin_ws/src/capstone_test/scripts/right_arm_wave.py";
std::string command_2 = "python /home/capstone/catkin_ws/src/capstone_test/scripts/dance.py";
std::string command_3 = "python /home/capstone/catkin_ws/src/capstone_test/scripts/initialization.py";

std::string test_command = "python right_arm_wave.py";

uint32_t commandID_one = 35;
uint32_t commandID_two = 350;
uint32_t commandID_three = 650;


void movementCallBack(const capstone_test::VisionCommand::ConstPtr& msg){
	
	//Right Arm Wave	
	if (commandID_one == msg->command.command_id){
		system(command_1.c_str());
	}

	//Dance
	else if (commandID_two == msg->command.command_id)
		system(command_2.c_str());

	//Initialization
	else if (commandID_three == msg->command.command_id)
		system(command_3.c_str());

}

int main(int argc, char * argv[]){
	//Py_Initialize();
	//PyRun_SimpleString("import sys");

	ros::init(argc, argv, "intermediate");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("intermediate/command", 10, movementCallBack);
	ros::Rate rate (10.0);

	while(n.ok()){
		ros::spinOnce();
		rate.sleep();
	}

	//Py_Finalize();
	return 0;

}
















