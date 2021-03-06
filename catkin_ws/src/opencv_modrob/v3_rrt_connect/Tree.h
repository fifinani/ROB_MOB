#ifndef TREE_H
#define TREE_H
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include <iostream>
#include "Node.h"

//#include "fct_comp.h"
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
      std::cout << "afficher liste des noeuds liés" << '\n';
    for (size_t i = 0; i < list_node.size(); i++) {
      std::cout<< "node["<<i << "]"<<getNodeAt(i).getPoint();
      getNodeAt(i).afficher_liste_noeuds();
    }
  }

  void draw_line_tree(Mat image);

  //std::vector<int>& chemin(Node node0, Node node_final);
  void chemin(std::vector<int>& indices, Node node0, Node node_final);

  int find_elem(std::vector<int> vect, int k);


    void affiche_vect(std::vector<int> v){
      std::cout << "vect=[" << '\n';
      for (size_t i = 0; i <v.size() ; i++) {
          std::cout << v[i] << ",";
      }
      std::cout << "]" << '\n';
      std::cout    << '\n';
    }


    void draw_pathway(Mat image, std::vector<int> vect_indices);


    void drawPoint(Mat image ){
        for (size_t i = 0; i < getlength(); i++) {
            circle(image, getNodeAt(i).getPoint(),5, Scalar(255,0,00),-1);
        }
    }

    vector<int> connected(Tree tree);


};


#endif
