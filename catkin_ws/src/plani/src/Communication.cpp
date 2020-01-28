#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseStamped.h>
#include "Communication.h"
using namespace cv;
using namespace std;




Communication::Communication(vector<Point> vecteurPoint )
{
    this->pos_courante=0;
    this->vecteurDePoint=vecteurPoint;
    pos_pub_ = nh_.advertise<geometry_msgs::PoseStamped>("/position", 1 );
    autorisation_sub_ = nh_.subscribe("Autorisation_node", 1000, &Communication::Callback, this);

}

void Communication::Callback(const geometry_msgs::PoseStamped& autorisation )
{

  point.x=vecteurDePoint[this->pos_courante].x;
  point.y=vecteurDePoint[this->pos_courante].y;
  pointstamped.pose.position =point;
  pointstamped.header.frame_id = "map";
  //pos_pub_ = nh_.advertise<geometry_msgs::PoseStamped>("/position", taille );
  pos_pub_.publish(pointstamped);
  pos_courante++;

}
