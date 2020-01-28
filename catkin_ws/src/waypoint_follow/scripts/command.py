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
from tf2_msgs.msg  import TFMessage

class Command :



    def objective_callback(self,data):
        self.R = data;

        return;

    def odom_callback(self,data):
        k1 = 0.2
        k2 = 1
        k3 = 5* k1
        Rt = PoseStamped()
        now = rospy.Time.now()
        self.R.header.stamp = now
        self.tf_listener_.waitForTransform("map", "base_footprint",now , rospy.Duration(4.0))
        Rt = self.tf_listener_.transformPose("base_footprint",self.R)
        position, quaternion = self.tf_listener_.lookupTransform("map","base_footprint",now)
        ang = euler_from_quaternion(quaternion)
        theta = ang[2]
        print (theta)

        self.V[0] = math.sqrt((Rt.pose.position.x)*(Rt.pose.position.x)+(Rt.pose.position.y)*(Rt.pose.position.y))
        self.V[1] = math.atan((Rt.pose.position.y)/(Rt.pose.position.x))
        self.V[2] = self.V[1] - theta
        print("robot")
        print(position[0])
        print(position[1])
        print("objective")
        print(self.R.pose.position.x)
        print(self.R.pose.position.y)
        self.vel_msg.linear.x = k1 * self.V[0]
        self.vel_msg.angular.z = k3 * self.V[2]
        return;

    def update(self):
        self.pub_twist.publish(self.vel_msg)
        return

    def __init__(self, *args) :
        self.vel_msg = Twist();
        self.vel_msg.linear.x = 0
        self.vel_msg.linear.y = 0
        self.vel_msg.linear.z = 0
        self.vel_msg.angular.x = 0
        self.vel_msg.angular.y = 0
        self.vel_msg.angular.z= 0
        self.R = PoseStamped()
        self.R.pose.position.x = 0
        self.R.pose.position.y = 0
        self.R.header.frame_id = 'map'
        self.V = np.array([0,0,0]).T
        self.tf_listener_ = tf.TransformListener()
        self.pub_twist = rospy.Publisher('/cmd_vel',Twist, queue_size=10)
        self.pub_objective = rospy.Publisher('/objective',PoseStamped, queue_size=10)
        rospy.Subscriber('/move_base_simple/goal', PoseStamped,self.objective_callback);
        rospy.Subscriber('/odom', Odometry,self.odom_callback);



if __name__ == '__main__':

    rospy.init_node('command')
    command = Command()
    rate = rospy.Rate(100) # 10hz
    while not rospy.is_shutdown():

        try:
            command.update()
        except rospy.ROSInterruptException:
            pass
        rate.sleep()
