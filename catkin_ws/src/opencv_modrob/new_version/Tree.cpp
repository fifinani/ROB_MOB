
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
    //return list_node[key_val];
    return key_val;
}


void Tree::insert(Node node){
//  list_node.insert(list_node.begin(), pos, node);
    list_node.push_back(node);
}

Tree::~Tree(){
}

//draw line
void Tree::draw_line_tree(Mat image){
  for (size_t i = 0; i <getList().size(); i++) {
    getNodeAt(i).draw_line(image,rand()%255, rand()%255, rand()%255 );
  }
}


void Tree::chemin(std::vector<int>& indices, Node node0, Node node_final){
    std::vector<int> vect_ind;
    Node node_cmp=node_final;
    bool reach=false;
    int it=0;
    int found=0;
    affiche_vect(indices);
    while ((reach==false)){
        //std::cout << "reach="<<reach << '\n';
        affiche_vect(vect_ind);
        found=0;
        for (size_t i = 0; i < getlength(); i++) {
            if (found==0){
                std::cout << "arbre  ["<<i <<"]"<< '\n';
                it=0;
                it=getNodeAt(i).find_node(node_cmp);
                if(it==0){
                        std::cout << "not found" << '\n';
                }
                else if (it==1){
                    std::cout << "FOUND IT" << '\n';
                    vect_ind.push_back(i);
                    node_cmp=getNodeAt(i);
                    found=1;

                }
            }

        }
        if (find_elem(vect_ind,0)==1){
            std::cout << "0 present" << '\n';
            reach=true;
        }


            //    waitKey(0);
        std::cout << "it =" << it<< '\n';
        std::cout<<"size=" << vect_ind.size() << '\n';
    /*
      //  it=2;
        std::cout << "node cmp=" << node_cmp.getPoint()<< '\n';
        std::cout  << '\n';
        */
      }
      affiche_vect(vect_ind);
      indices=vect_ind;
      return ;//vect_ind;

}

void Tree::draw_pathway(Mat image, std::vector<int> vect_indices){
    for (size_t i = 0; i <vect_indices.size()-1; i++) {
      line(image, getNodeAt(vect_indices[i]).getPoint(),getNodeAt(vect_indices[i+1]).getPoint(), Scalar(0,0,255), 2, 8, 0);
      //std::cout << "taille=" << vect_indices.size();
      //getNodeAt(vect_indices[i]).draw_line(image,0, 0, 255 );
  }
}
