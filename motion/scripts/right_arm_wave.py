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
		char = self.name[0]
		goal.trajectory.joint_names = ['right_shoulder_tip', 'right_shoulder', 'right_upper_arm', 'right_elbow']
		point = JointTrajectoryPoint()
		point.positions = angles
		point.time_from_start = rospy.Duration(1)
		goal.trajectory.points.append(point)
			
		self.jta.send_goal_and_wait(goal)

	def reset_speed(self):
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
	arm = Joint('r_arm')
	arm.move_joint([0,0.0445,0,-0.285]) #init
	arm.move_joint([0,0.769,0.6136,1.246]) #wave set up/right
	arm.move_joint([0,0.769,-0.814,1.246]) #wave left
	arm.move_joint([0,0.769,0.6136,1.246]) #wave right
	arm.move_joint([0,0.769,-0.814,1.246]) #wave left
	arm.move_joint([0,0.0445,0,-0.285])  #end

	arm.reset_speed()

if __name__ == '__main__':
	rospy.init_node('right_arm_wave_tester')
	main()
