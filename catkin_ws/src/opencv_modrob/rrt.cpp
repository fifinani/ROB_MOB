#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "opencv/cv.h"
#include "btree.h"

using namespace cv
using namespace std

Mat image;

int main( int argc, char** argv )
{
    //loadimage();
    return 0;
}


int extend(btree tree, Point point){

  Point nearest_point= nearest_neighbour(point, tree);
  if (new_state(point, nearest_point, Point new_point, float new_command)==1){
      tree.insert(tree.getNode());



  }

  return 1;
}

//trouve le plus proche voisin
Point nearest_neighbour(Point pt, btree t){
  //parcours les nodes de l'arbre et compare les abscisses et ordonnées des différents points avec le point voulu

  
}

//fonction
int new_state(Point x, Point x_near, Point x_new, float  commande){
//  float delta_t;
  return 1;
}

//charge image
int loadimage(){


  image = imread("carte.png", CV_LOAD_IMAGE_COLOR);   // Read the file

  if(! image.data )                              // Check for invalid input
  {
      cout <<  "Could not open or find the image" << std::endl ;
      return -1;
  }


  namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
  imshow( "Display window", image );                   // Show our image inside it.

  waitKey(0);                                          // Wait for a keystroke in the window


}
