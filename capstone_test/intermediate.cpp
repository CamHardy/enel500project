#include <ros/ros.h>
#include <iostream>
#include <Python.h>
#include <std_msgs/String.h>

void movementCallback(const std_msgs::String::ConstPtr& msg){
	string temp = msg->data.c_str();
	ROS_INFO("Command is: [%s]", temp); 
}

int main(int argc, char * argv[]){
	string test;
	Py_Initialize();

	PyRun_SimpleString("import sys");

	ros::init(argc, argv, "intermediate");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("intermediate/command", 1000, movementCallBack);
	ros::Rate rate (10.0);

	while(n.ok()){
		ros::spinOnce();
		rate.sleep();
	}

	Py_Finalize();
	return 0;

}
