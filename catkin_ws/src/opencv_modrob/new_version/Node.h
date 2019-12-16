#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;


class Node{
public:
    cv::Point point;
    int key_value;
    int order_value;
    std::vector<Node> node_linked;

  public:
      Node();
      Node(cv::Point point, int key_value, int order_value);

      cv::Point getPoint(){
        return point;
      }

      int getValNode(){
        return key_value;
      }

      int getValOder(){
        return order_value;
      }

      ~Node(){

      }

      void  setKey(int key_value){
        this->key_value=key_value;
      }

      int getKey(){
        return key_value;
      }

      int getlength(){
        return node_linked.size();
      }

      void insert(Node node);

      Node& getNodeAt(int i){
        return node_linked[i];
      }

      void afficher_liste_noeuds(){
        std::cout << "liste noeuds=";
        for (size_t i = 0; i< node_linked.size() ; i++) {
          std::cout << getNodeAt(i).getPoint() ;
        }
        std::cout << "" << '\n';
      }

      std::vector<Node>& get_linkedList(){
        return node_linked;

      }


      void draw_line(Mat img, int r, int g,int b){
        int size=get_linkedList().size();


        if(size>=1){
          line(img, getPoint(), getNodeAt(0).getPoint(), Scalar(r,g,b), 2, 8, 0);
          for (size_t i = 0; i < size-1 ; i++) {
          //  std::cout << "size= " << size<< '\n';
            //afficher_liste_noeuds();
            std::cout << getNodeAt(i).getPoint() << '\n';
            std::cout << getNodeAt(i+1).getPoint() << '\n';
            line(img, getNodeAt(i).getPoint(), getNodeAt(i+1).getPoint(), Scalar(r,g,b), 2, 8, 0);
          }
        }
      }
};
