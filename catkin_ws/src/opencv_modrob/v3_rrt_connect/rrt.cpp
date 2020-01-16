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
    char chemin[]="../../projet_rob_mob/maps/map.pgm";
    loadimage(chemin);

    //initialisation de l'arbre et des points de départ et d'arrivé
    Point point1(250,250);
    Node node1(point1,0,0);
    Tree tree1(node1);
    Node node2(Point(350,300),1,1);
    Node node3(Point(152,5),1,1);
    Node node_final(Point(350,300),1,1);
    Tree tree2(node_final);

    //indice du node le plus proche
    int closest_node, closest_node2;
    Node connected_node;
    Node new_node, new_node2;// point aléatoire
    Node node_added, node_added2;//point reellement ajouté
    bool reached=false;//condition de fin de boucle (si le nouveau point aux alentours du point finale)
    namedWindow( "Display window", WINDOW_AUTOSIZE );
    // dilatation
    Mat element1 = getStructuringElement( MORPH_ELLIPSE,Size( 10,10),Point(-1,-1) );
    dilate(img_bin, img_bin, element1, Point(-1,-1), 1, BORDER_CONSTANT);
    imshow("img bin", img_bin);
    Point new_point, new_point2;
    int q=10;

    int i=1;
    int dir=0;
    int dir2=0;
  //  std::vector<Point> vect_point;

    while(!reached){


        new_node=Node( Point(rand()%width, rand()%height),i,i );
/////////////////////////////////////////////////////
        closest_node=tree1.getClosest(new_node);
        dir=tree1.getNodeAt(closest_node).direction(new_node);
        new_point=tree1.getNodeAt(closest_node).NewPos(new_node, q, width, dir);
        //circle(image, new_point,5, Scalar(0,255,255),-1);
        //    std::cout << "new point ="<< new_point << '\n';
        node_added=Node(new_point,i,i );
        if(node_added.needLink(img_bin)==0){
            if( node_added.get_distance(node_final)<q  ){
                reached=true;
                std::cout << "REACH" << '\n';
                node_added.insert(node_final);
            }
            tree1.insert(node_added);
            tree1.getNodeAt(closest_node).insert(node_added);
            //affichage
            circle(image, node_added.getPoint(),5, Scalar(0,255,255),-1);
        }//fin if


/////////////////////////////////////////////////////
          if(reached==true){
              //node_added.insert(node2);
              std::cout << "fin "<<node_added.getNodeAt(0).getPoint()<< '\n';
             // tree1.getNodeAt(closest_node).insert(node_added);
              tree1.insert(node_final);
          }
//////////////////////////////////////////////////////

          //tree1.getNodeAt(closest_node).afficher_liste_noeuds();
          circle(image, node1.getPoint(),5, Scalar(0,0,255),-1);
          circle(image, node_final.getPoint(),5, Scalar(0,255,0),-1);
          //circle(image, tree1.getNodeAt(i).getPoint(),5, Scalar(255,0,00),-1);


          imshow( "Display window", image );

          tree1.drawPoint(image);
          //tree1.draw_line_tree(image);
          //waitKey(10);
          //tree1.afficher_arbre();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        new_node2=Node( Point(rand()%width, rand()%height),i,i );
        /////////////////////////////////////////////////////
        closest_node2=tree2.getClosest(new_node2);
        dir2=tree2.getNodeAt(closest_node2).direction(new_node2);
        new_point2=tree2.getNodeAt(closest_node2).NewPos(new_node2, q, width, dir2);
        //circle(image, new_point,5, Scalar(0,255,255),-1);
        //    std::cout << "new point ="<< new_point << '\n';
        node_added2=Node(new_point2,i,i );
        if(node_added2.needLink(img_bin)==0){

            tree2.insert(node_added2);
            tree2.getNodeAt(closest_node2).insert(node_added2);
            //affichage
            circle(image, node_added2.getPoint(),5, Scalar(255,0,255),-1);
        }//fin

        //changer connected en liste de point
        //connected_node.setPoint(Point(tree1.connected(tree2)));
        std::vector<int> vecteur_point;
        vecteur_point=tree1.connected(tree2);
        if(vecteur_point.size()==2){
            std::cout << "2 TREES ARE CONNECTED" << '\n';
            circle(image, connected_node.getPoint(),5, Scalar(255,255,255),-1);
            reached=true;
            std::cout << "closest node to connected_node=" << tree1.getNodeAt(tree1.getClosest(tree2.getNodeAt(vecteur_point[1]) )).getPoint() <<'\n';
            /*
            tree1.insert(connected_node);
            tree1.getNodeAt(tree1.getClosest(connected_node)).insert(connected_node);
            */



        }
        //waitKey(0);

        i++;
    }//fin while

    imshow( "Display window", image );
    waitKey(0);
    tree1.afficher_liste_noeuds_linked();
    circle(image, connected_node.getPoint(),5, Scalar(0,0,255),-1);
    tree1.drawPoint(image);
    waitKey(0);
    std::vector<int> indices, indices2;
    tree1.chemin(indices, node1, connected_node);
//    tree2.chemin(indices2, connected_node, node_final);
    tree1.draw_pathway(image, indices) ;

    imshow("bin", img_bin);
    waitKey(0);
    /**********************************************************/

    //affiche les noeuds liés a chaque noeuds
//    tree1.afficher_liste_noeuds_linked();
    //affiche arbre complet
//    tree1.afficher_arbre();


    /*********************************************************/
    //affiche fenetre
    imshow( "Display window", image );
    // Show our image inside it.
    //imshow("gris", img_grey);
    imshow("bin", img_bin);
    waitKey(0);                              // Wait for a keystroke in the window

    return 0;
}

/*******************************************************************************/
//charge image
int loadimage(char* chemin){

  image = imread(chemin , CV_LOAD_IMAGE_COLOR);   // Read the file
  cvtColor(image, img_grey,COLOR_BGR2GRAY); //On passe l'image en niveau de gris
	threshold(img_grey, img_bin,210,250,THRESH_BINARY_INV    );
	//30,210

  width=image.size().width;
  height=image.size().height;
  int val=int(img_bin.at<uchar>(Point(200,200)) );
  std::cout << "val=" << val<< '\n';

  return 0;

}
