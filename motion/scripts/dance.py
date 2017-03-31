#!/usr/bin/env python
import roslib
import sys
roslib.load_manifest('motion')

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

	def move_joint(self, angles):
		goal = FollowJointTrajectoryGoal()
		goal.trajectory.joint_names = ['left_shoulder', 'left_elbow', 'right_shoulder', 'right_elbow', 'waist']
		point = JointTrajectoryPoint()
		point.positions = angles
		point.time_from_start = rospy.Duration(1)
		goal.trajectory.points.append(point)
			
		self.jta.send_goal_and_wait(goal)

	def reset_speed(self):
		rospy.wait_for_service('/left_shoulder_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/left_shoulder_controller/set_speed', SetSpeed, persistent=True)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/left_elbow_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/left_elbow_controller/set_speed', SetSpeed, persistent=True)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/right_shoulder_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/right_shoulder_controller/set_speed', SetSpeed, persistent=True)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/right_elbow_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/right_elbow_controller/set_speed', SetSpeed, persistent=True)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/hip_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/right_elbow_controller/set_speed', SetSpeed, persistent=True)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

def main():
	dance = Joint('dance')
	
	dance.move_joint([-0.0138,-0.2577,0.05,-0.284,2.35])#init dance

	dance.move_joint([-0.0138,1.45,0.05,1.45,2.35])#init arms

	dance.move_joint([-0.0138,1.45,0.733,1.45,0.44])#right arm up
	dance.move_joint([-1.155,1.45,0.05,1.45,3.95])#left arm up

	dance.move_joint([-0.0138,1.45,0.733,1.45,0.44])#right arm up
	dance.move_joint([-1.155,1.45,0.05,1.45,3.95])#left arm up

	dance.move_joint([-0.0138,1.45,0.733,1.45,0.44])#right arm up
	dance.move_joint([-1.155,1.45,0.05,1.45,3.95])#left arm up

	dance.move_joint([-0.0138,1.45,0.733,1.45,0.44])#right arm up
	dance.move_joint([-1.155,1.45,0.05,1.45,3.95])#left arm up

	dance.move_joint([-0.0138,1.45,0.733,1.45,0.44])#right arm up
	dance.move_joint([-1.155,1.45,0.05,1.45,3.95])#left arm up

	dance.move_joint([-0.0138,1.45,0.733,1.45,0.44])#right arm up
	dance.move_joint([-1.155,1.45,0.05,1.45,3.95])#left arm up

	dance.move_joint([-0.0138,-0.2577,0.05,-0.284,2.35])#move back to initial positions

	dance.reset_speed() #reset the speed of all the motors used

if __name__ == '__main__':
	rospy.init_node('dance_tester')
	main()
