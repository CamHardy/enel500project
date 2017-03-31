#!/usr/bin/env python
import rospy
from capstone_test.msg import VisionCommand

def talker():
	pub = rospy.Publisher('/intermediate/command', VisionCommand)
	rospy.init_node('intermediate_test_publisher', anonymous=True)
	r = rospy.Rate(10)
	msg = VisionCommand()
	msg.command.command_id = 21
	msg.object.display_x = 0
	msg.object.display_y = 0
	msg.object.distance_z = 0

	while not rospy.is_shutdown():
		rospy.loginfo(msg)
		pub.publish(msg)
		msg.command.command_id = msg.command.command_id + 1
		r.sleep()


if __name__ == '__main__':
	try:
		talker()
	except rospy.ROSInterruptException: pass
