
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "Node.h"
using namespace cv;
using namespace std;

Node::Node(){

}

Node::Node( cv::Point point, int key_value, int order_value){
  this->key_value=key_value;
  this->order_value=order_value;
  this->point=point;
  //this->node_linked=NULL;

}

void Node::insert(Node node){
//  list_node.insert(list_node.begin(), pos, node);
    node_linked.push_back(node);
}
