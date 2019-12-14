
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "Tree.h"
using namespace cv;
using namespace std;

/*
Tree::Tree(){

}*/

Tree::Tree(){

}
Tree::Tree(Node node){
  this->first_node=node;
  this->list_node.push_back(node);

}

Node Tree::getClosest(Node node){
  int dist_x=abs(first_node.getPoint().x-node.getPoint().x);
  int dist_y=0;
  int key_val=0;
  for (size_t i = 0; i < this->list_node.size(); i++) {
  //  std::cout << i << '\n';
    //std::cout << "point x ="<<this->list_node[i].getPoint().x  << '\n';
    //std::cout << "node x=" << node.getPoint().x << '\n';
    //std::cout <<"dist=" <<abs(this->list_node[i].getPoint().x-node.getPoint().x) << '\n';
    if ( dist_x > abs(this->list_node[i].getPoint().x-node.getPoint().x)){
        key_val=i;
        dist_x=abs(this->list_node[i].getPoint().x-node.getPoint().x);
    }

  }
  //std::cout << "fin boucle" << '\n';
  return list_node[key_val];
}


void Tree::insert(Node node, int pos){
//  list_node.insert(list_node.begin(), pos, node);
    list_node.push_back(node);
}

Tree::~Tree(){

  }
