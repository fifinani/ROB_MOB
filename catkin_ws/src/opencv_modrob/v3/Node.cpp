
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <cmath>    
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

//calcule la distance entre 2 nodes
float Node::get_distance(Node node2){
    int x1=getPoint().x;
    int y1=getPoint().y;
    int x2=node2.getPoint().x;
    int y2=node2.getPoint().y;
    int dist= sqrt(pow((x2-x1),2)+pow((y2-y1),2));
    return dist;

}


void Node::draw_line(Mat img, int r, int g,int b){
    int size=get_linkedList().size();
    if(size>=1)
    {
      line(img, getPoint(), getNodeAt(0).getPoint(), Scalar(r,g,b), 2, 8, 0);
      for (size_t i = 0; i < size-1 ; i++)
            line(img, getNodeAt(i).getPoint(), getNodeAt(i+1).getPoint(), Scalar(r,g,b), 2, 8, 0);
      }
}


/*int Node::find_node_in_linked_list(Node node){
	std::vector<int>::iterator it = std::find(get_linkedList().begin(), get_linkedList().end(), node.get);
	if (it != vecOfNums.end())
		std::cout << "Element Found" << std::endl;
	else
		std::cout << "Element Not Found" << std::endl;

	// Get index of element from iterator
	int index = std::distance(vecOfNums.begin(), it);
	std::cout << index << std::endl;
	return index;


}*/

int Node::compare_node(Node node){
    if(node.getPoint()==getPoint())
      return 1;
    else
      return 0;
}

int Node::find_node(Node node1){
    for (size_t i = 0; i < get_linkedList().size(); i++) {
        //std::cout << "i find node =" <<i << '\n';
        if(getNodeAt(i).compare_node(node1)==1){
            //std::cout << "we find it" << '\n';
            return 1;
        }
    }
   return 0;
}
