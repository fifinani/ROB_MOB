#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "Node.h"

class Tree{

private:
  std::vector<Node> list_node;
  Node first_node;

public:
  Tree(Node node);

  Node getFirstNode(){
    return first_node;
  }

  int getlength(){
    return list_node.size();
  }

  Node getClosest(Node node){
    int dist_x=first_node.getPoint().x-node.getPoint().x;
    int dist_y=0;
    int key_val=0;
    for (size_t i = 0; i < length(this.getlength()); i++) {

      if (dist_x > list_node[i].getPoint().x-node.getPoint().x){
          key_val=i;
          dist_x=list_node[i].getPoint().x-node.getPoint().x;
      }

    }
  }



};
