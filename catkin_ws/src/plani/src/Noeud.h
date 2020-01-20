#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cstddef>
#include "opencv2/core/version.hpp"
#if CV_MAJOR_VERSION == 2
// do opencv 2 code
#elif CV_MAJOR_VERSION == 3
// do opencv 3 code
#endif

using namespace cv;
using namespace std;


class Noeud{
public:
    cv::Point point;
    int key_value;
    int order_value;
    std::vector<Noeud> node_linked;

  public:
      //constructeur et destructeur
      Noeud();
      Noeud(cv::Point point, int key_value, int order_value);
      ~Noeud(){}

      //fetter & setter
      cv::Point getPoint(){
        return point;
      }

      void setPoint(cv::Point point1){
         this->point.x=point1.x;
         this->point.y=point1.y;

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
      Noeud& getNodeAt(int i){
        return node_linked[i];
      }

      void insert(Noeud node);


      //affiche tous les noeuds liés
      void afficher_liste_noeuds(){
        std::cout << "liste noeuds=";
        for (size_t i = 0; i< node_linked.size() ; i++) {
          std::cout << getNodeAt(i).getPoint() ;
        }
        std::cout << "" << '\n';
      }

      //recupere la liste des noeuds liés
      std::vector<Noeud>& get_linkedList(){
        return node_linked;

      }

      //trace les lignes entre tous les noeuds liés
      void draw_line(Mat img, int r, int g,int b);

      float get_distance( Noeud node2);

      int compare_node(Noeud node);

      int find_node(Noeud node1);

      //verifie que le pixel n'est pas blanc
      int needLink(Mat image){
          int val=int(image.at<uchar>(getPoint()) );
          int v= int(val==250);//210
          //std::cout << "point "<< getPoint()<<"pixel=" << v<<"val="<<val << '\n';
          if (v==0) {
              return 0;
          }
          else
            return 1 ;

      }

      int noObstacle(Mat image, Noeud node){
          //for (size_t i = 0; i < count; i++) {
              /* code */
          //}
      }

      std::vector<int> findEquation(Noeud node){
          std::vector<int> xyz;
          int a=node.getPoint().y - getPoint().y;
          int b=getPoint().x - node.getPoint().x;
          int c= a*getPoint().x + b*getPoint().y;
          xyz.push_back(a);
          xyz.push_back(b);
          xyz.push_back(c);

          return xyz;
      }


      cv::Point NewPos(Noeud node, int q , int width, int dir) {
          std::vector<int> xyz=findEquation(node);
          double x=0;
          double y=0;
          int x1=getPoint().x;
          int y1=getPoint().y;
          double a=xyz[0];
          double b=xyz[1];
          double c=xyz[2];
          double dif1=0;
          double dif2=0;
          int nb=0;
          double xf=0;
          double yf=0;
          double erreur=0;
          //std::cout << "xyz="<<a<<","<<b<<"," <<c<< '\n';
        //  float dist= sqrt(pow((0-x1),2)+pow((0-y1),2));
          bool cond=true;
          if(b==0){
                cond=false;
            //    std::cout << "b=0" << '\n';
            }
          double dist=0.0;
          for (size_t i = 0; i < width; i++) {
              if (cond){
                  //std::cout << "dans boucle" << '\n';
                  //std::cout << "xyz="<<a<<","<<b<<"," <<c<< '\n';
                  //std::cout << "q=" <<q<< '\n';
                  //std::cout << "["<<i <<","<<float(  (c-a*i)/b  )<<"]" << '\n';
                  //std::cout << "x1="<<x1<<", y1="<<y1 << '\n';

                  //(x2-x1)²
                  dif1=(x1-i)*(x1-i);
                  //(y2-y1)²
                  dif2=( y1 - ((c-a*i)/b) ) *( y1 - ((c-a*i)/b) );

                  //std::cout << "(x2-x1)²=" << dif1<< ", "<< "(y2-y1)²="<< dif2  << '\n';
                  dist=sqrt( dif1+ dif2  );
                  //std::cout << "dist_calculé ="<<dist << '\n';
                  //std::cout << "erreur="<< abs(dist-q) << '\n';
                  //std::cout <<"c="<<c<<",b="<<b<<",a="<<a<< ",x = "<<i <<", y = "<<(c-a*i)/b << "//"<< c-a*i<<"//"<< a/b<<'\n';
                  erreur=abs((double)dist-q);
                  //std::cout << "erreur= "<<(double)(dist-q) << '\n';
                  if(erreur<.5){
                    //  std::cout << "erreur= "<<(dist-(float)q) << '\n';
                      x=i;
                      y=(c-a*i)/b;
                      nb++;

                    //  std::cout << "found" << '\n';
                    //  cond=false;
                 }
                 //std::cout << "x="<<x<<",y="<<y << '\n';
                 if (dir==0 && x>getPoint().x){// si a droite
                        //std::cout << " node à droite" << '\n';
                         xf=x;
                         yf=y;

                 }
                 if (dir==1 && (x<getPoint().x)){// si a gauche
                        //std::cout << "node à gauche" << '\n';
                        xf=x;
                        yf=y;

                }

            }//fin cond


          }
          return Point(xf,yf);
      }

    int direction(Noeud node){
        int direction=getPoint().x-node.getPoint().x;
        if (direction<0)// node à droite
            return 0;
        else//node a gauche
            return 1;

      }




};
