#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "node.h"

Node:Node( cv::Point point, int key_value, int order_value){
  this->key_value=key_value;
  this->order_value=order_value;
  this->point=point;
  this->node_linked=NULL;

}
