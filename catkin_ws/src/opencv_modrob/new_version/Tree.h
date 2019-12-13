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

  ~Tree(){

  }
  void insert(Node node, int pos);




};
