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
      //constructeur et destructeur
      Node();
      Node(cv::Point point, int key_value, int order_value);
      ~Node(){}

      //fetter & setter
      cv::Point getPoint(){
        return point;
      }

      int getValNode(){
        return key_value;
      }

      int getValOder(){
        return order_value;
      }

      void  setKey(int key_value){
        this->key_value=key_value;
      }

      int getKey(){
        return key_value;
      }

      //récupère la longueur de la liste des noeuds liés
      int getlength(){
        return node_linked.size();
      }

      //récupère le noeud lié à la  position i
      Node& getNodeAt(int i){
        return node_linked[i];
      }

      void insert(Node node);


      //affiche tous les noeuds liés
      void afficher_liste_noeuds(){
        std::cout << "liste noeuds=";
        for (size_t i = 0; i< node_linked.size() ; i++) {
          std::cout << getNodeAt(i).getPoint() ;
        }
        std::cout << "" << '\n';
      }

      //recupere la liste des noeuds liés
      std::vector<Node>& get_linkedList(){
        return node_linked;

      }

      //trace les lignes entre tous les noeuds liés
      void draw_line(Mat img, int r, int g,int b);

      int get_distance( Node node2);

      int compare_node(Node node);

      int find_node(Node node1);

      //verifie que le pixel n'est pas blanc
      int needLink(Mat image){
          int val=int(image.at<uchar>(getPoint()) );
          int v= int(val==210);
          std::cout << "point "<< getPoint()<<"pixel=" << v<<"val="<<val << '\n';
          if (v==0) {
              return 0;
          }
          else
            return 1 ;

      }

      int noObstacle(Mat image, Node node){
          //for (size_t i = 0; i < count; i++) {
              /* code */
          //}


      }
};
