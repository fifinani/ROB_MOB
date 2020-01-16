#!/usr/bin/env python
import rospy
import math
import numpy as np
from numpy.linalg import inv
from std_msgs.msg import String
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import Pose
from geometry_msgs.msg import Point
from move_base_msgs.msg import MoveBaseActionResult
from geometry_msgs.msg import Quaternion
from tf.transformations import euler_from_quaternion

l1 = 1
ang = [0,0,0]
theta = 0
P = Point(0,0,0)
R = Point(0,0,0)
V = np.array([0,0]).T
U = np.array([0,0]).T
M = np.array([[1,0],[0,1]])
k1 = 0.5
k2 = 0.5

vel_msg = Twist();
vel_msg.linear.x = 0
vel_msg.linear.y = 0
vel_msg.linear.z = 0
vel_msg.angular.x = 0
vel_msg.angular.y = 0
vel_msg.angular.z = 0



def odom_callback(data):
    x = data.pose.pose.position.x;
    y = data.pose.pose.position.y;
    quaternion = [data.pose.pose.orientation.x,data.pose.pose.orientation.y,data.pose.pose.orientation.z,data.pose.pose.orientation.w];
    ang = euler_from_quaternion(quaternion)
    theta = ang[2];
    P.x = x+ l1*math.cos(theta);
    P.y = y+ l1*math.sin(theta);
    M = np.array([[math.cos(theta),-l1*math.sin(theta)],[math.sin(theta),l1*math.cos(theta)]]);
    V[0] = -k1 * (P.x-R.x);
    V[1] = -k2 * (P.y-R.y);
    print(str(theta))
    return;

def objective_callback(data):
    R.x = data.pose.position.x;
    R.y = data.pose.position.y;
    return;

def trajectoire():
    U = np.dot(inv(M),V);
    vel_msg.linear.x = U[0]
    vel_msg.angular.z = U[1]

    return vel_msg;


def waypoint_follow():
    pub_twist = rospy.Publisher('/cmd_vel',Twist, queue_size=10)
    rospy.Subscriber('/move_base_simple/goal', PoseStamped,objective_callback);
    rospy.Subscriber("/odom",Odometry,odom_callback);
    rospy.init_node('command');
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        pub_twist.publish(trajectoire())
        rate.sleep();

if __name__ == '__main__':

    try:
        waypoint_follow()
    except rospy.ROSInterruptException:
        pass
