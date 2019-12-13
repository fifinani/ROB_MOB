#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;

struct node
{
  int key_value;
  int nb_key=length(point_list);
  vector<node> point_list;
//  int pixel_x;
//  int pixel_y;
  cv::Point point;
};


class Btree
{

  private:
  //méthodes
          /*void destroy_tree(node *leaf);
          void insert(int key, node *leaf);
          node *search(int key, node *leaf);
          */
  //arguments
    node* root;


  public:
    Btree(node* node1 );
    //~Btree();

        /*void insert(int key);
        node *search(int key);
        void destroy_tree();
        */

    node* getNode(){
      return root;
    }

    int getNn_key(){
      return nb_key;
    }

    void setNb_key(int nb){
      this->nb_key=nb;
    }

    cv::Point getPoint(){
      return (*root).point;
    }

    ~Btree()
    {
      //destroy_tree();
    }
};
