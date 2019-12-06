#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import String
from geometry_msgs import Twist
from nav_msgs import Odometry
from geometry_msgs import PoseStamped
from geometry_msgs import Pose
# move_base package
objective = Pose()
odom = Pose()

def odom_callback(data):
    odom = data.pose.pose;
    return

def waypoint_callback(data):
    objective = data;
    return

def trajectoire():
    twist = Twist()
    pub.publish(twist)

def waypoint_follow():
    pub = rospy.Publisher('cmd_vel', Twist, queue_size=10)
    rospy.Subscriber("odom",Odometry,odom_callback);
    rospy.Subscriber("objective",Pose,waypoint_callback)
    rospy.init_node('waypoint_follow', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        trajectoire()
        rate.sleep()

if __name__ == '__main__':
    try:
        waypoint_follow()
    except rospy.ROSInterruptException:
        pass
