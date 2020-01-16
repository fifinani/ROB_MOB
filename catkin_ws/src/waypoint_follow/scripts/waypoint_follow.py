#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import String
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import Pose
from move_base_msgs.msg import MoveBaseActionResult
x = 0;
next = False;
def result_callback(data):
    next = True;
    return;

def nextObjective():
    objective = PoseStamped();
    x = x+10;
    objective.pose.position.x = x;
    objective.pose.position.y = 0;
    objective.pose.position.z = 0;
    return objective;

def trajectoire(pub):
    if(next):
        objective = nextObjective();
        next = False;
        pub.publish(objective);
    return;


def waypoint_follow():
    pub = rospy.Publisher('/move_base_simple/goal', PoseStamped, queue_size=10)
    rospy.Subscriber("/move_base/result",MoveBaseActionResult,result_callback);
    rospy.init_node('waypoint_follow', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        trajectoire(pub);
        rate.sleep();

if __name__ == '__main__':
    try:
        waypoint_follow()
    except rospy.ROSInterruptException:
        pass
