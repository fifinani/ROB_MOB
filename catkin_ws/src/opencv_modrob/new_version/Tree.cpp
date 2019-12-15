
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

int Tree::getClosest(Node node){
  int x_a,y_a,x_n,y_n, x_f,y_f;
  x_n=node.getPoint().x;
  y_n=node.getPoint().y;

  x_f=first_node.getPoint().x;
  y_f=first_node.getPoint().y;
  int dist= sqrt(pow((x_f-x_n),2)+pow((y_f-y_n),2));
  //abs(first_node.getPoint().x-node.getPoint().x);

  int key_val=0;
  for (size_t i = 0; i < this->list_node.size(); i++) {
    x_a=this->list_node[i].getPoint().x;
    y_a=this->list_node[i].getPoint().y;
    x_n=node.getPoint().x;
    y_n=node.getPoint().y;
    if ( dist > sqrt(pow((x_a-x_n),2)+pow((y_a-y_n),2))  ){
        key_val=i;
        dist=sqrt(pow((x_a-x_n),2)+pow((y_a-y_n),2));
    }

  }
  //std::cout << "fin boucle" << '\n';
  //return list_node[key_val];
  return key_val;
}


void Tree::insert(Node node){
//  list_node.insert(list_node.begin(), pos, node);
    list_node.push_back(node);
}

Tree::~Tree(){

  }
