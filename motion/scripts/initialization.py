#!/usr/bin/env python
import sys
sys.path.append('/home/capstone/catkin_ws/devel/lib/python2.7/dist-packages')
sys.path.append('/opt/ros/kinetic/lib/python2.7/dist-packages')
import roslib
roslib.load_manifest('motion')

import rospy
import actionlib
from std_msgs.msg import Float64
import trajectory_msgs.msg 
import control_msgs.msg  
from trajectory_msgs.msg import JointTrajectoryPoint
from control_msgs.msg import JointTrajectoryAction, JointTrajectoryGoal, FollowJointTrajectoryAction, FollowJointTrajectoryGoal
from dynamixel_controllers.srv import *

class Joints:
	def __init__(self, motor_name):
		self.name = motor_name
		self.jta = actionlib.SimpleActionClient('/'+self.name+'_controller/follow_joint_trajectory', FollowJointTrajectoryAction)
		rospy.loginfo('Waiting for joint trajectory action')
		self.jta.wait_for_server()
		rospy.loginfo('Found joint trajectory action!')

	def move_joints(self, angles):
		goal = FollowJointTrajectoryGoal()
		char = self.name[0]
		goal.trajectory.joint_names = ['head','neck','left_shoulder_tip','left_shoulder','left_upper_arm','left_elbow','right_shoulder_tip','right_shoulder','right_upper_arm','right_elbow','spine','waist']
		point = JointTrajectoryPoint()
		point.positions = angles
		point.time_from_start = rospy.Duration(1)
		goal.trajectory.points.append(point)
			
		self.jta.send_goal_and_wait(goal)

	def reset_speeds(self):
		rospy.wait_for_service('/head_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/head_controller/set_speed', SetSpeed, persistent=True)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/neck_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/neck_controller/set_speed', SetSpeed, persistent=True)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/left_shoulder_tip_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/left_shoulder_tip_controller/set_speed', SetSpeed, persistent=True)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/left_shoulder_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/left_shoulder_controller/set_speed', SetSpeed, persistent=True)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/left_upper_arm_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/left_upper_arm_controller/set_speed', SetSpeed, persistent=True)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/left_elbow_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/left_elbow_controller/set_speed', SetSpeed, persistent=True)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/right_shoulder_tip_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/right_shoulder_tip_controller/set_speed', SetSpeed, persistent=True)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/right_shoulder_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/right_shoulder_controller/set_speed', SetSpeed, persistent=True)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/right_upper_arm_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/right_upper_arm_controller/set_speed', SetSpeed, persistent=True)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/right_elbow_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/right_elbow_controller/set_speed', SetSpeed, persistent=True)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/spine_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/spine_controller/set_speed', SetSpeed, persistent=True)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e

		rospy.wait_for_service('/hip_controller/set_speed')
		try:
			set_head_speed = rospy.ServiceProxy('/hip_controller/set_speed', SetSpeed, persistent=True)
			set_head_speed(0.5)
		except rospy.ServiceException, e:
			print "Service call failed: %s"%e


def main():
	robot = Joints('initialization')
	robot.move_joints([5.6,1.566,2.804,-0.0138,-0.003,-0.2577,-0.007,0.05,0,-0.284,3.14,2.35])
	robot.reset_speeds()

if __name__ == '__main__':
	rospy.init_node('initialization_tester')
	main()
