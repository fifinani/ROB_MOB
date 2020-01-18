#include <cstdlib>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <time.h>
#include <iostream>
#include <cmath>

#include "Tree.h"
#include "rrt.h"

#include <geometry_msgs/Point.h>
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>

//#include <image_transport/image_transport.h>
    //#include <cv_bridge/cv_bridge.h>
    //#include <sensor_msgs/image_encodings.h>#include "opencv2/core/version.hpp"
#if CV_MAJOR_VERSION == 2
// do opencv 2 code
#elif CV_MAJOR_VERSION == 3
// do opencv 3 code
#endif
/*
    #include <opencv2/imgproc/imgproc.hpp>
    #include <opencv2/highgui/highgui.hpp>
*/
using namespace cv;
using namespace std;

Mat image, img_grey, img_bin;
int width, height;

int x_rand[10], y_rand[10];


int main( int argc, char** argv )
{
    srand (time(NULL));
    char chemin[]="../../../map.pgm";
    loadimage(chemin);

    //initialisation de l'arbre et des points de départ et d'arrivé
    Point point1(250,250);
    Noeud node1(point1,0,0);
    Tree tree1(node1);
    Noeud node2(Point(350,300),1,1);
    Noeud node3(Point(152,5),1,1);
    Noeud node_final(Point(300,300),1,1);

    //indice du node le plus proche
    int closest_node, closest_node2;
    std::cout << "/* message */" << '\n';
    Noeud new_node;// point aléatoire
    Noeud node_added;//point reellement ajouté
    bool reached=true;//condition de fin de boucle (si le nouveau point aux alentours du point finale)
    namedWindow( "Display window", WINDOW_AUTOSIZE );
    // dilatation
    Mat element1 = getStructuringElement( MORPH_ELLIPSE,Size( 10,10),Point(-1,-1) );
    dilate(img_bin, img_bin, element1, Point(-1,-1), 1, BORDER_CONSTANT);
    imshow("img bin", img_bin);
    Point new_point;
    int q=10;
    waitKey(0);
    int i=1;
    int dir=0;
  //  std::vector<Point> vect_point;

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
