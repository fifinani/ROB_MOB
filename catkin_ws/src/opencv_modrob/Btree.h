#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <iostream>

struct node
{
//  int key_value;
  node *left;
  node *right;
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


    cv::Point getPoint(){
      return (*root).point;
    }

    ~Btree()
    {
      //destroy_tree();
    }
};
