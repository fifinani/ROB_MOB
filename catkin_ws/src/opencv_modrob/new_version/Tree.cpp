#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "Tree.h"

Tree::Tree(Node node){
  first_node=node;
}

Node getClosest(Node node){
  int dist_x=this.first_node.getPoint().x-node.getPoint().x;
  int dist_y=0;
  int key_val=0;
  for (size_t i = 0; i < this->list_node.size(); i++) {

    if (dist_x > this->list_node[i].getPoint().x-node.getPoint().x){
        key_val=i;
        dist_x=this->list_node[i].getPoint().x-node.getPoint().x;
    }

  }
}


void insert(Node node, int pos){
  list_node.insert(list_node.begin(), pos);

}
