#!/usr/bin/env python
import rospy
import math
import numpy as np
import tf
from numpy.linalg import inv
from std_msgs.msg import String
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import Pose
from geometry_msgs.msg import Point
from geometry_msgs.msg import TransformStamped
from move_base_msgs.msg import MoveBaseActionResult
from geometry_msgs.msg import Quaternion
from tf.transformations import euler_from_quaternion

l1 = 0.1
ang = [0,0,0]
theta = 0
P = Point(0,0,0)
R = PoseStamped()
R.pose.position.x = 0
R.pose.position.y = 0

V = np.array([0,0,0]).T
U = np.array([0,0]).T
M = np.array([[1,0],[0,1]])
k1 = 0.5
k2 = 1
k3 = 0.5

vel_msg = Twist();
vel_msg.linear.x = 0
vel_msg.linear.y = 0
vel_msg.linear.z = 0
vel_msg.angular.x = 0
vel_msg.angular.y = 0
vel_msg.angular.z = 0

def odom_callback(data):
    m = TransformStamped()
    m.header.frame_id = '/map'
    m.child_frame_id = '/base_link'
    x = m.transform.translation.x
    y = m.transform.translation.y
    quaternion = [m.transform.rotation.x,m.transform.rotation.y,m.transform.rotation.z,m.transform.rotation.w];
    ang = euler_from_quaternion(quaternion)
    theta = ang[2];
    P.x = x+ l1*math.cos(theta);
    P.y = y+ l1*math.sin(theta);
    M = np.array([[math.cos(theta),-l1*math.sin(theta)],[math.sin(theta),l1*math.cos(theta)]]);
    V[0] = math.sqrt((P.x-R.x)*(P.x-R.x) +(P.y-R.y)*(P.y-R.y))
    V[1] = math.atan((P.y-R.y)/(P.x-R.x))
    V[2] = V[1]-theta
    print(V[0])
    print(V[1])
    print(V[2])
    return;

def objective_callback(data):
    tf_listener_ = tf.TransformListener()
    R = tf_listener_.transformPoint("/base_link", data)
    return;

def trajectoire():
    vel_msg.linear.x = k1 * V[0]
    vel_msg.angular.z = k3 * V[2]

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
