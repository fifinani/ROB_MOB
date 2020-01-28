#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseStamped.h>
#if CV_MAJOR_VERSION == 2
// do opencv 2 code
#elif CV_MAJOR_VERSION == 3
// do opencv 3 code
#endif

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class Communication
{
public:
  Communication(vector<Point> vecteurPoint );

private:

  void Callback(const geometry_msgs::PoseStamped& autorisation);

  ros::NodeHandle nh_;
  std::vector<cv::Point> vecteurDePoint;

  geometry_msgs::Point point;
  geometry_msgs::PoseStamped pointstamped;

  ros::Publisher pos_pub_;
  ros::Subscriber autorisation_sub_;
  int pos_courante;

};
