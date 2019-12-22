#include <cstdlib>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <time.h>
#include <iostream>
#include <cmath>
#include "opencv/cv.h"
#include "Tree.h"
#include "rrt.h"

using namespace cv;
using namespace std;

Mat image, img_grey, img_bin;
int width, height;

int x_rand[10], y_rand[10];


int main( int argc, char** argv )
{
    srand (time(NULL));
    char chemin[]="map2.pgm";
    loadimage(chemin);

    //initialisation de l'arbre et des points de départ et d'arrivé
    Point point1(50,50);
    Node node1(point1,0,0);
    Tree tree1(node1);
    Node node2(Point(150,150),1,1);
    Node node3(Point(152,5),1,1);
    Node node_final(Point(300,300),1,1);

    //indice du node le plus proche
    int closest_node, closest_node2;

    Node new_node;// point aléatoire
    Node node_added;//point reellement ajouté
    bool reached=false;//condition de fin de boucle (si le nouveau point aux alentours du point finale)
    namedWindow( "Display window", WINDOW_AUTOSIZE );
    // dilatation
    Mat element1 = getStructuringElement( MORPH_ELLIPSE,Size( 10,10),Point(-1,-1) );
    dilate(img_bin, img_bin, element1, Point(-1,-1), 1, BORDER_CONSTANT);

    Point new_point;
    int q=10;

    int i=1;
    int dir=0;
  //  std::vector<Point> vect_point;

    while(!reached){


        new_node=Node( Point(rand()%width, rand()%height),i,i );
    //    std::cout << "width="<<width << '\n';
    //    std::cout << "rand node ="<<new_node.getPoint() << '\n';
        //si pixel noir==pas sur un ostacle




        //else
        //    std::cout << "SUR NOIR" << '\n';

/////////////////////////////////////////////////////
        closest_node=tree1.getClosest(new_node);
        //circle(image, new_node.getPoint(),5, Scalar(0,255,255),-1);
    //    std::cout << "closest node ="<<tree1.getNodeAt(closest_node).getPoint() << '\n';

    //    std::vector<int> v=node1.findEquation(node2);
    //    tree1.affiche_vect(v);

        dir=tree1.getNodeAt(closest_node).direction(new_node);

        if (dir==1){
            //std::cout << "gauche"<< '\n';
        }

        if (dir==0){
            //std::cout << "droite" << '\n';
        }
        new_point=tree1.getNodeAt(closest_node).NewPos(new_node, q, width, dir);
        //circle(image, new_point,5, Scalar(0,255,255),-1);

        if (new_point.x==0 && new_point.y==0){
        //    std::cout << "no point" << '\n';
        }
        else{
        //    std::cout << "new point ="<< new_point << '\n';
            node_added=Node(new_point,i,i );
            if(node_added.needLink(img_bin)==0){


            if( node_added.get_distance(node2)<10  ){
                reached=true;
                std::cout << "REACH" << '\n';
                node_added.insert(node2);
            }
            tree1.insert(node_added);
            tree1.getNodeAt(closest_node).insert(node_added);

            //affichage
        //    circle(image, new_node.getPoint(),5, Scalar(0,255,255),-1);
            circle(image, node_added.getPoint(),5, Scalar(0,255,255),-1);
        //    line(image, new_node.getPoint(), tree1.getNodeAt(closest_node).getPoint(), Scalar(0,0,0), 2, 8, 0);
        //    line(image, new_node.getPoint(), node_added.getPoint(), Scalar(0,0,0), 2, 8, 0);

            /*if (tree1.getNodeAt(closest_node).getPoint()==node2.getPoint()){
                reached=true;
                std::cout << "REACH" << '\n';
                std::cout << " closest_node="<<tree1.getNodeAt(closest_node).getPoint()<<"// node finale= "<<node2.getPoint() << '\n';
                node_added.insert(node2);
            }*/

        }//fin else



/////////////////////////////////////////////////////
          if(reached==true){
              //node_added.insert(node2);
              std::cout << "fin "<<node_added.getNodeAt(0).getPoint()<< '\n';
             // tree1.getNodeAt(closest_node).insert(node_added);
              tree1.insert(node2);
          }
//////////////////////////////////////////////////////

          //tree1.getNodeAt(closest_node).afficher_liste_noeuds();
          circle(image, node1.getPoint(),5, Scalar(0,0,255),-1);
          circle(image, node2.getPoint(),5, Scalar(0,255,0),-1);
          //circle(image, tree1.getNodeAt(i).getPoint(),5, Scalar(255,0,00),-1);
      }
          imshow( "Display window", image );

          //waitKey(0);
          i++;
          tree1.drawPoint(image);
        //  tree1.draw_line_tree(image);
          waitKey(10);
          //tree1.afficher_arbre();

    }//fin while

    imshow( "Display window", image );
    waitKey(0);

    tree1.drawPoint(image);
    waitKey(0);
    std::vector<int> indices;
    tree1.chemin(indices, node1, node2);
    //tree1.afficher_liste_noeuds_linked();
    tree1.draw_pathway(image, indices) ;

    imshow("bin", img_bin);
    waitKey(0);
    /**********************************************************/

    //affiche les noeuds liés a chaque noeuds
    tree1.afficher_liste_noeuds_linked();
    //affiche arbre complet
    tree1.afficher_arbre();


    /*********************************************************/
    //affiche fenetre
    imshow( "Display window", image );
    // Show our image inside it.
    imshow("gris", img_grey);
    imshow("bin", img_bin);
    waitKey(0);                              // Wait for a keystroke in the window

    return 0;
}

/*******************************************************************************/
//charge image
int loadimage(char* chemin){

  image = imread(chemin , CV_LOAD_IMAGE_COLOR);   // Read the file
  cvtColor(image, img_grey,COLOR_BGR2GRAY); //On passe l'image en niveau de gris
	threshold(img_grey, img_bin,30,210,THRESH_BINARY_INV );


  width=image.size().width;
  height=image.size().height;


  return 0;

}
