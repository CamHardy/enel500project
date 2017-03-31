#!/usr/bin/env python
import roslib
import sys
roslib.load_manifest('capstone_test')

import rospy
import actionlib
from std_msgs.msg import Float64
import trajectory_msgs.msg 
import control_msgs.msg  
from trajectory_msgs.msg import JointTrajectoryPoint
from control_msgs.msg import JointTrajectoryAction, JointTrajectoryGoal, FollowJointTrajectoryAction, FollowJointTrajectoryGoal
from dynamixel_controllers.srv import *

class Joint:
	def __init__(self, motor_name):
		self.name = motor_name
		self.jta = actionlib.SimpleActionClient('/'+self.name+'_controller/follow_joint_trajectory', FollowJointTrajectoryAction)
		rospy.loginfo('Waiting for joint trajectory action')
		self.jta.wait_for_server()
		rospy.loginfo('Found joint trajectory action!')

	def move_right_joint(self, angles):
		goal = FollowJointTrajectoryGoal()
		char = self.name[0]
		goal.trajectory.joint_names = ['right_shoulder_tip', 'right_shoulder', 'right_upper_arm', 'right_elbow']
		point = JointTrajectoryPoint()
		point.positions = angles
		point.time_from_start = rospy.Duration(1)
		goal.trajectory.points.append(point)
			
		self.jta.send_goal_and_wait(goal)

	def move_left_joint(self, angles):
		goal = FollowJointTrajectoryGoal()
		char = self.name[0]
		goal.trajectory.joint_names = ['left_shoulder_tip', 'left_shoulder', 'left_upper_arm', 'left_elbow']
		point = JointTrajectoryPoint()
		point.positions = angles
		point.time_from_start = rospy.Duration(1)
		goal.trajectory.points.append(point)
			
		self.jta.send_goal_and_wait(goal)

	def reset_speed(self):
		rospy.wait_for_service('/left_shoulder_tip_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/left_shoulder_tip_controller/set_speed', SetSpeed)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/left_shoulder_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/left_shoulder_controller/set_speed', SetSpeed)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/left_upper_arm_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/left_upper_arm_controller/set_speed', SetSpeed)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/left_elbow_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/left_elbow_controller/set_speed', SetSpeed)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

	        rospy.wait_for_service('/right_shoulder_tip_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/right_shoulder_tip_controller/set_speed', SetSpeed)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/right_shoulder_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/right_shoulder_controller/set_speed', SetSpeed)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/right_upper_arm_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/right_upper_arm_controller/set_speed', SetSpeed)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/right_elbow_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/right_elbow_controller/set_speed', SetSpeed)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e


def main():
	right_arm = Joint('r_arm')
	left_arm = Joint('l_arm')

	right_arm.move_right_joint([-0.007,0.05,0,1.244]) #init right arm
	left_arm.move_left_joint([2.804,-0.0138,-0.003,1.450]) #init left arm

	right_arm.move_right_joint([0,0.773,0,1.244]) #move right arm up
	left_arm.move_left_joint([2.804,-1.155,0,1.450]) #move left arm up

	right_arm.move_right_joint([-0.007,0.05,0,1.244]) #init right arm
	left_arm.move_left_joint([2.804,-0.0138,-0.003,1.450]) #init left arm

	right_arm.move_right_joint([0,0.773,0,1.244]) #move right arm up
	left_arm.move_left_joint([2.804,-1.155,0,1.450]) #move left arm up

	right_arm.move_right_joint([-0.007,0.05,0,1.244]) #init right arm
	left_arm.move_left_joint([2.804,-0.0138,-0.003,1.450]) #init left arm

	right_arm.move_right_joint([0,0.773,0,1.244]) #move right arm up
	left_arm.move_left_joint([2.804,-1.155,0,1.450]) #move left arm up

	right_arm.move_right_joint([-0.007,0.05,0,-0.284]) #reset to initial positions
	left_arm.move_left_joint([2.804,-0.0138,-0.003,-0.2577]) #reset to initial positions

	right_arm.reset_speed() #reset the speed of all the motors used

if __name__ == '__main__':
	rospy.init_node('dance_tester')
	main()
