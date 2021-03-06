#include <cstdlib>
#include <unistd.h>
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
    char chemin[]="maptest.pgm";
    loadimage(chemin);

    Point point1(50,50);
    Node node1(point1,0,0);
    Tree tree1(node1);
    Node node2(Point(150,150),1,1);
    Node node3(Point(152,5),1,1);
    Node node_final(Point(300,300),1,1);
  //  tree1.insert(node2,1);
    //tree1.insert(node3,1);
  //  cout <<"get closest node"<<endl;
  //  Node node4;

    //node4=tree1.getClosest(node3);
    //std::cout << "node4= "<<node4.getPoint() << '\n';

    //cout<<tree1.getList().size()<<endl;
    //cout<<tree1.getNodeAt(0).getPoint()<<endl;
    int closest_node, closest_node2;
    Node new_node;
    bool reached=false;
    namedWindow( "Display window", WINDOW_AUTOSIZE );



    int i=1;
  //  std::vector<Point> vect_point;
    //for (size_t i = 1; i <= 4; i++) {
    while(!reached){

      new_node=Node( Point(rand()%width, rand()%height),i,i );

      if( new_node.get_distance(node2)<20  ){
        reached=true;
        std::cout << "REACH" << '\n';
        new_node.insert(node2);
      }

      //si pixel noir==pas sur un ostacle
      if(new_node.needLink(img_bin)==0){

          closest_node=tree1.getClosest(new_node);
          tree1.getNodeAt(closest_node).insert(new_node);
          tree1.insert( new_node );
      }
      else std::cout << "SUR NOIR" << '\n';

      if(reached==true){
          tree1.insert(node2);
      }


      //tree1.getNodeAt(closest_node).afficher_liste_noeuds();
      //vect_point.push_back(Point(rand()%width, rand()%height  ) );
      circle(image, tree1.getNodeAt(i).getPoint(),5, Scalar(255,0,00),-1);
      circle(image, node1.getPoint(),5, Scalar(0,0,255),-1);
      circle(image, node2.getPoint(),5, Scalar(0,255,0),-1);
      circle(image, node3.getPoint(),5, Scalar(0,255,255),-1);
      i++;

      imshow( "Display window", image );
      //tree1.draw_line_tree(image);
      waitKey(100);
    }
    imshow( "Display window", image );
    waitKey(0);

    std::vector<int> indices;
    tree1.chemin(indices, node1, node2);
    tree1.afficher_liste_noeuds_linked();
    //std::cout<<"length"<<tree1.getlength()  << '\n';
    //imshow( "Display window", image );
    /*for (size_t i = 0; i <indices.size()-1; i++) {
  //line(image, getNodeAt(vect_indices[i]).getPoint(),getNodeAt(vect_indices[i+1]).getPoint(), Scalar(0,0,255), 2, 8, 0);
        std::cout << "taille=" << indices.size()<<'\n';
    }*/

    tree1.draw_pathway(image, indices) ;

    /*for (int i = 0; i < indices.size(); i++) {
        std::cout << tree1.getNodeAt(indices[i]).getPoint() << '\n';
    }
    */
/*
    closest_node=tree1.getClosest(node2);
    tree1.getNodeAt(closest_node).insert(node2);
    std::cout << "key=" << tree1.getNodeAt(closest_node).getKey()<<'\n';
    std::cout << "closest_node=" << closest_node<< '\n';
    tree1.getNodeAt(closest_node).setKey(50);
    std::cout << "key=" << tree1.getNodeAt(closest_node).getKey()<<'\n';
    tree1.insert(node2);
    tree1.getNodeAt(closest_node).afficher_liste_noeuds();

    circle(image,tree1.getNodeAt(closest_node).getPoint() ,5, Scalar(0,200,255),-1);
*/    //line(image, node1.getPoint(), node2.getPoint(), Scalar(0,0,0), 2, 8, 0);
    //std::cout << tree1.getList().size()<< '\n';



    /*for (size_t i = 0; i <tree1.getList().size(); i++) {
      tree1.getNodeAt(i).draw_line(image,rand()%255, rand()%255, rand()%255 );
    }**/
    //std::cout << "first node point"<< tree1.getFirstNode().getPoint()<< '\n';
    //std::cout << "first node list" << '\n';
    //tree1.getNodeAt(0).afficher_liste_noeuds();
    //std::cout << "all node list" << '\n';
    /*********************************************************/
  /*  closest_node2=tree1.getClosest(node3);
    tree1.getNodeAt(closest_node2).insert(node3);
    std::cout << "key=" << tree1.getNodeAt(closest_node2).getKey()<<'\n';
    std::cout << "closest_node=" << closest_node2<< '\n';
    tree1.getNodeAt(closest_node2).setKey(50);
    std::cout << "key=" << tree1.getNodeAt(closest_node2).getKey()<<'\n';
    tree1.insert(node3);
    tree1.getNodeAt(closest_node2).afficher_liste_noeuds();

*/
    /**********************************************************/

    //affiche les noeuds liés a chaque noeuds
    //tree1.afficher_liste_noeuds_linked();
    //affiche arbre complet
    tree1.afficher_arbre();


    /*********************************************************/
    //affiche fenetre
      imshow( "Display window", image );
    // Show our image inside it.
    imshow("gris", img_grey);
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
