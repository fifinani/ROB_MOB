#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <time.h>
#include <iostream>
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
    char chemin[]="map.pgm";
    loadimage(chemin);

    Point point1(50,50);
    Node node1(point1,0,0);
    Tree tree1(node1);
    Node node2(Point(150,54),1,1);
    Node node3(Point(152,5),1,1);
  //  tree1.insert(node2,1);
    //tree1.insert(node3,1);
  //  cout <<"get closest node"<<endl;
  //  Node node4;

    //node4=tree1.getClosest(node3);
    //std::cout << "node4= "<<node4.getPoint() << '\n';

    //cout<<tree1.getList().size()<<endl;
    //cout<<tree1.getNodeAt(0).getPoint()<<endl;

  //  std::vector<Point> vect_point;
    for (size_t i = 1; i <= 8; i++) {
      tree1.insert( Node( Point(rand()%width, rand()%height),i,i ) );
    //  vect_point.push_back(Point(rand()%width, rand()%height  ) );
      circle(image, tree1.getNodeAt(i).getPoint(),5, Scalar(255,0,00),-1);

    }
    circle(image, node1.getPoint(),5, Scalar(0,0,255),-1);
    circle(image, node2.getPoint(),5, Scalar(0,255,0),-1);
    circle(image, node3.getPoint(),5, Scalar(0,255,255),-1);

    int closest_node, closest_node2;
    closest_node=tree1.getClosest(node2);
    tree1.getNodeAt(closest_node).insert(node2);
    std::cout << "key=" << tree1.getNodeAt(closest_node).getKey()<<'\n';
    std::cout << "closest_node=" << closest_node<< '\n';
    tree1.getNodeAt(closest_node).setKey(50);
    std::cout << "key=" << tree1.getNodeAt(closest_node).getKey()<<'\n';
    tree1.insert(node2);
    tree1.getNodeAt(closest_node).afficher_liste_noeuds();

    circle(image,tree1.getNodeAt(closest_node).getPoint() ,5, Scalar(0,200,255),-1);



    /*********************************************************/
    closest_node2=tree1.getClosest(node3);
    tree1.getNodeAt(closest_node2).insert(node3);
    std::cout << "key=" << tree1.getNodeAt(closest_node2).getKey()<<'\n';
    std::cout << "closest_node=" << closest_node2<< '\n';
    tree1.getNodeAt(closest_node2).setKey(50);
    std::cout << "key=" << tree1.getNodeAt(closest_node2).getKey()<<'\n';
    tree1.insert(node3);
    tree1.getNodeAt(closest_node2).afficher_liste_noeuds();


    /**********************************************************/


    //affiche arbre complet
    tree1.afficher_arbre();
    //affiche fenetre
    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", image );                   // Show our image inside it.
    //imshow("gris", img_grey);
    //imshow("bin", img_bin);
    waitKey(0);                                          // Wait for a keystroke in the window

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


  //cout<<vect_point<<endl;


//  for (size_t i = 1; i <= width; i++) {
    /*if ( int(img_bin.at<uchar>(i,15) )==1){
      cout<<"trouvé"<<endl;
      cout<<"val de i="<<i<<endl;
    }*/
  /*    cout<<"val="<< int(img_bin.at<uchar>(i,(int)(height/2)))<<endl;
    cout<<"val de i="<<i<<endl;
    cout<<width<<endl;
  }*/

  //cout<<"val="<< int(img_bin.at<uchar>(0,0))<<endl;
  //cout<< "x_rand="<<x_rand<<"y_rand="<<y_rand<<endl;


/*  namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
  imshow( "Display window", image );                   // Show our image inside it.
  //imshow("gris", img_grey);
  imshow("bin", img_bin);
  waitKey(0);                                          // Wait for a keystroke in the window
*/  return 0;

}




/*******************************************************************************/
/*
int extend(Btree tree, Point point){

  Point nearest_point= nearest_neighbour(point, tree);
  if (new_state(point, nearest_point, Point new_point, float new_command)==1){
      tree.insert(tree.getNode());

  }

  return 1;
}
*/
//trouve le plus proche voisin
/*Point nearest_neighbour(Point pt, Btree t){
  //parcours les nodes de l'arbre et compare les abscisses et ordonnées des différents points avec le point voulu
  if(t.getPoint().x<pt.x){

  }

}*/
/*
//fonction
int new_state(Point x, Point x_near, Point x_new, float  commande){
//  float delta_t;
  return 1;
}
*/
