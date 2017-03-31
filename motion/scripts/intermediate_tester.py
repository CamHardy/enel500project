#!/usr/bin/env python
import roslib
import rospy
import sys
import os
import time

roslib.load_manifest('motion')

from robot_msgs.msg import VisionCommand

class Tester():
    def __init__(self):
	rospy.init_node('intermediate_test_publisher', anonymous=True)

	self.msg = VisionCommand()
	self.msg.command.command_id = -1
	self.msg.object.display_x = 0
	self.msg.object.display_y = 0
	self.msg.object.distance_z = 0

	self.cmd_sel = False
	self.cmd = -1

	self.crude_command = 0

	#self.vision_test_position = 0

	rospy.loginfo("INTERMEDIATE TEST. WILL NOT BE IMPLEMENTED IN THE FINAL SOLUTION OF THE ROBOT")

    def set_command(self):
	while self.cmd_sel == False:
		print "This is a mock interaction interface with the vision team."
		print "Select a command from the following to simulate options found on the GUI"
		print "I: Initialize the motors. (SET TO INITIAL POSITIONS)"
		print "R: Simulate a right arm wave. (MOVE RIGHT ARM MOTORS)"
		print "D: Simulate a dance. (MOVE BODY MOTORS)"
		print "C: Run the previous commands in a loop. (DO ALL OF THE ABOVE; DOES NOT STOP)"
		#print"M: Run a dummy vision interface node. (HEAD AND NECK MOVEMENT)"
		print "Q: Quit taking commands. (TERMINATE NODE)"
		temp_var = raw_input(">>>")
		
		if (temp_var == "i" or temp_var == "I"):
			self.cmd = 0
			self.cmd_sel = True

		elif (temp_var == "r" or temp_var == "R"):
			self.cmd = 1
			self.cmd_sel = True

		elif (temp_var == "d" or temp_var == "D"):
			self.cmd = 2
			self.cmd_sel = True

		elif (temp_var == "c" or temp_var == "C"):
			self.cmd = 3
			self.cmd_sel = True

		#else if (temp_var == "m" || temp_var == "M"):
			#self.cmd = 4
			#cmd_sel = True

		elif (temp_var == "q" or temp_var == "Q"):
			print "Node will terminate. Relaunch using terminal for more testing."
			sys.exit()

		else:
			print "Invalid input. Try again."
			time.sleep(2)
			os.system('clear')
	
    def set_simple_msg(self):
	if self.cmd == 0: 
		self.msg.command.command_id = 0
		self.msg.object.display_x = 0
		self.msg.object.display_y = 0
		self.msg.object.distance_z = 0
	if self.cmd == 1: 
		self.msg.command.command_id = 1
		self.msg.object.display_x = 0
		self.msg.object.display_y = 0
		self.msg.object.distance_z = 0
	if self.cmd == 2: 
		self.msg.command.command_id = 2
		self.msg.object.display_x = 0
		self.msg.object.display_y = 0
		self.msg.object.distance_z = 0

    def set_msg(self):
	if self.cmd == 3:
		if self.msg.command.command_id > 2000:
			self.msg.command.command_id = 1000
		self.msg.command.command_id = self.msg.command.command_id + 1
    
    def msg_reset(self):
	self.msg.command.command_id = 69
	self.msg.object.display_x = 0
	self.msg.object.display_y = 0
	self.msg.object.distance_z = 0
	#if self.cmd == 4:
		#msg.command.command_id = 4;		
		#time.sleep(2)
		#if self.vision_test_position = 0
		#	self.msg.object.display_x = 0.52
		#	self.msg.object.display_y = 0
		#else if self.vision_test_position = 1
		#	self.msg.object.display_x = 0
		#	self.msg.object.display_y = -0.2
		#else if self.vision_test_position = 2
		#	self.msg.object.display_x = 0.6
		#	self.msg.object.display_y = -0.4
		#else if self.vision_test_position = 3
		#	self.msg.object.display_x = -0.3
		#	self.msg.object.display_y = 0.5


    def talker(self):
	self.set_command()
	if (self.cmd >= 0 and self.cmd <= 2):
		self.set_simple_msg()
	else:
		self.msg.command.command_id = 1000		
		self.set_msg()
	
	
	self.pub = rospy.Publisher('/robot/vision/vision_command', VisionCommand, queue_size=10)
	rospy.init_node('intermediate_test_publisher', anonymous=True)
	self.r = rospy.Rate(10)

	if (self.cmd >= 0 and self.cmd <= 2):
		while self.crude_command < 50:
			rospy.loginfo(self.msg)
			self.pub.publish(self.msg)
			self.r.sleep()
			self.crude_command = self.crude_command + 1
			if self.crude_command >= 50:
				self.crude_command = 0
				self.msg_reset()
				while self.crude_command < 50:
					self.pub.publish(self.msg)
					self.r.sleep()
					self.crude_command = self.crude_command + 1
				self.crude_command = 0
				break

	elif (self.cmd == 3):
		while not rospy.is_shutdown():
			self.set_msg()
			rospy.loginfo(self.msg)
			self.pub.publish(self.msg)
			self.r.sleep()

	self.cmd_sel = False

if __name__ == '__main__':
	try:
		test_node = Tester()
		while True:
			test_node.talker()
	except rospy.ROSInterruptException: pass
