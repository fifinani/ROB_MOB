#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <time.h>
#include <iostream>
#include "opencv/cv.h"
#include "Btree.h"

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
    //arbre1 départ
    node* root_tree1= (node *) malloc (sizeof (node));
    root_tree1->left=NULL;
    root_tree1->right=NULL;
    root_tree1->point=Point(0,0);
    Btree tree1(root_tree1);

    //arbre2 destination
    node* root_tree2= (node *) malloc (sizeof (node));
    root_tree2->left=NULL;
    root_tree2->right=NULL;
    root_tree2->point=Point(1,2);
    Btree tree2(root_tree2);

    cout<<tree2.getPoint()<<endl;
    cout<<tree1.getPoint()<<endl;

    std::vector<Point> vect_point;
    for (size_t i = 0; i < 10; i++) {
      vect_point.push_back(Point(rand()%width, rand()%height  ) );
      circle(img_bin, vect_point[i],5, Scalar(255,0,00),-1);

    }

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", image );                   // Show our image inside it.
    //imshow("gris", img_grey);
    imshow("bin", img_bin);
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

//trouve le plus proche voisin
Point nearest_neighbour(Point pt, Btree t){
  //parcours les nodes de l'arbre et compare les abscisses et ordonnées des différents points avec le point voulu
  if(t.getPoint().x<pt.x){
  
}

}

//fonction
int new_state(Point x, Point x_near, Point x_new, float  commande){
//  float delta_t;
  return 1;
}
*/
