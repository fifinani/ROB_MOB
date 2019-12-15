
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "Node.h"
using namespace cv;
using namespace std;

class Tree{

public:
  std::vector<Node> list_node;
  Node first_node;

public:
  Tree();
  Tree(Node node);


  Node& getFirstNode(){
    return first_node;
  }

  int getlength(){
    return list_node.size();
  }

  ~Tree();

  void insert(Node node);

  int getClosest(Node node);

  vector<Node> getList(){
    return list_node;
  };

  Node& getNodeAt(int i){
    return list_node[i];
  }

  void afficher_arbre(){
    std::cout << "arbre=" << '\n';
    for (size_t i = 0; i< list_node.size() ; i++) {
      std::cout << getNodeAt(i).getPoint() << '\n';
    }
  }

  void afficher_liste_noeuds_linked(){
    for (size_t i = 0; i < list_node.size(); i++) {
      std::cout << "node["<<i << "]";
      getNodeAt(i).afficher_liste_noeuds();
    }

  }
/*  void draw(){
    for (size_t i = 0; i < count; i++) {

    }

  }
*/
};
