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

      int getlength(){
        return node_linked.size();
      }

      void insert(Node node);

      Node getNodeAt(int i){
        return node_linked[i];
      }

      void afficher_liste_noeuds(){
        std::cout << "liste noeuds=" << '\n';
        for (size_t i = 0; i< node_linked.size() ; i++) {
          std::cout << getNodeAt(i).getPoint() << '\n';
        }
      }
};
