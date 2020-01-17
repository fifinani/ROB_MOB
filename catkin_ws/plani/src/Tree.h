#ifndef TREE_H
#define TREE_H
#pragma once
#include <stdlib.h>
#include <stdio.h>
//#include <image_transport/image_transport.h>
//    #include <cv_bridge/cv_bridge.h>
    //#include <sensor_msgs/image_encodings.h>
//    #include <opencv2/imgproc/imgproc.hpp>
//    #include <opencv2/highgui/highgui.hpp>

#include "opencv2/core/version.hpp"
#if CV_MAJOR_VERSION == 2
// do opencv 2 code
#elif CV_MAJOR_VERSION == 3
// do opencv 3 code
#endif
#include <opencv2/opencv.hpp>
#include <cmath>

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include "Noeud.h"

//#include "fct_comp.h"
using namespace cv;
using namespace std;

class Tree{

public:
  std::vector<Noeud> list_node;
  Noeud first_node;

public:
  Tree();
  Tree(Noeud node);


  Noeud& getFirstNode(){
    return first_node;
  }

  int getlength(){
    return list_node.size();
  }

  ~Tree();

  void insert(Noeud node);

  int getClosest(Noeud node);

  vector<Noeud> getList(){
    return list_node;
  };

  Noeud& getNodeAt(int i){
    return list_node[i];
  }

  void afficher_arbre(){
    std::cout << "arbre=" << '\n';
    for (int i = 0; i< list_node.size() ; i++) {
      std::cout << getNodeAt(i).getPoint() << '\n';
    }
  }

  void afficher_liste_noeuds_linked(){
      std::cout << "afficher liste des noeuds liés" << '\n';
    for (int i = 0; i < list_node.size(); i++) {
      std::cout<< "node["<<i << "]"<<getNodeAt(i).getPoint();
      getNodeAt(i).afficher_liste_noeuds();
    }
  }

  void draw_line_tree(Mat image);

  //std::vector<int>& chemin(Noeud node0, Noeud node_final);
  void chemin(std::vector<int>& indices, Noeud node0, Noeud node_final);

  int find_elem(std::vector<int> vect, int k){
      // Check if the element k is in vector
      std::vector<int>::iterator it = std::find(vect.begin(), vect.end(), k);
      if (it != vect.end()){
          //std::cout << "Element Found" << std::endl;
          return 1;
      }
      else{
         // std::cout << "Element Not Found" << std::endl;
          return 0;
      }
      waitKey(0);
  }


    void affiche_vect(std::vector<int> v){
      std::cout << "vect=[" << '\n';
      for (int i = 0; i <v.size() ; i++) {
          std::cout << v[i] << ",";
      }
      std::cout << "]" << '\n';
      std::cout    << '\n';
    }


    void draw_pathway(Mat image, std::vector<int> vect_indices);


    void drawPoint(Mat image ){
        for (int i = 0; i < getlength(); i++) {
            circle(image, getNodeAt(i).getPoint(),5, Scalar(255,0,00),-1);
        }
    }

};

/*

*/
#endif
