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
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#if CV_MAJOR_VERSION == 2
// do opencv 2 code
#elif CV_MAJOR_VERSION == 3
// do opencv 3 code
#endif

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat image, img_grey, img_bin;
int width, height;

int x_rand[10], y_rand[10];




void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    Point* p=(Point*)userdata;
    //std::cout << "point="<<p << '\n';
    if  ( event == EVENT_LBUTTONDOWN )
    {
        cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
        p->x=x;
        p->y=y;

    }

}



int main( int argc, char** argv )
{
    srand (time(NULL));
    char chemin[]="my_map.pgm";
    loadimage(chemin);
    imshow("image", image);
    waitKey(0);


    //indice du node le plus proche
    int closest_node, closest_node2;
    Noeud connected_node, connected_node2;
    Noeud new_node, new_node2;// point aléatoire
    Noeud node_added, node_added2;//point reellement ajouté
    bool reached=false;//condition de fin de boucle (si le nouveau point aux alentours du point finale)
    namedWindow( "Display window", WINDOW_NORMAL );
    // dilatation
    Mat element1 = getStructuringElement( MORPH_ELLIPSE,Size( 10,10),Point(-1,-1) );
    dilate(img_bin, img_bin, element1, Point(-1,-1), 1, BORDER_CONSTANT);

    Point pointDeDepart, pointDeFin;
    pointDeDepart=Point(250,250);
    pointDeFin=Point(350,300);
    std::cout << "choix de point de départ" << '\n';
    setMouseCallback("Display window", CallBackFunc, &pointDeDepart);
    imshow("Display window", img_bin);
    waitKey(0);
    setMouseCallback("Display window",NULL,NULL);
    std::cout << "Point de départ=" <<pointDeDepart<< '\n';

    std::cout << "choix du point d'arrivée" << '\n';
    setMouseCallback("Display window", CallBackFunc, &pointDeFin);
    imshow("Display window", img_bin);
    waitKey(0);
    setMouseCallback("Display window",NULL,NULL);
    std::cout << "Point de fin=" <<pointDeFin<< '\n';



    //initialisation de l'arbre et des points de départ et d'arrivé
    Point point1(250,250);
    Noeud node1(pointDeDepart,0,0);
    Tree tree1(node1);
    Noeud node2(Point(350,300),1,1);
    Noeud node3(Point(152,5),1,1);
    Noeud node_final(pointDeFin,1,1);
    Tree tree2(node_final);
    Point new_point, new_point2;
    waitKey(0);
    //distance
    int q=10;
    int i=1;
    //direction new point for tree1
    int dir=0;
    //direction new point for tree2
    int dir2=0;
    //vecteur contenant les indices des noeuds de connection
    std::vector<int> vecteur_point;

    //tant que les 2 arbres ne sont connectés
    while(!reached){

        new_node=Noeud( Point(rand()%width, rand()%height),i,i );
/////////////////////////////////////////////////////
        closest_node=tree1.getClosest(new_node);
        dir=tree1.getNodeAt(closest_node).direction(new_node);
        new_point=tree1.getNodeAt(closest_node).NewPos(new_node, q, width, dir);
        //circle(image, new_point,5, Scalar(0,255,255),-1);
        //    std::cout << "new point ="<< new_point << '\n';
        node_added=Noeud(new_point,i,i );
        //si node sur zone autorisée
        if(node_added.needLink(img_bin)==0){
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

        tree1.drawPoint(image);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        new_node2=Noeud( Point(rand()%width, rand()%height),i,i );
        /////////////////////////////////////////////////////
        closest_node2=tree2.getClosest(new_node2);
        dir2=tree2.getNodeAt(closest_node2).direction(new_node2);
        new_point2=tree2.getNodeAt(closest_node2).NewPos(new_node2, q, width, dir2);
        node_added2=Noeud(new_point2,i,i );
        if(node_added2.needLink(img_bin)==0){

            tree2.insert(node_added2);
            tree2.getNodeAt(closest_node2).insert(node_added2);
            //affichage
            circle(image, node_added2.getPoint(),5, Scalar(255,0,255),-1);
        }//fin

        //changer connected en liste de point
        vecteur_point=tree1.connected(tree2);
        if(vecteur_point.size()==2){
            std::cout << "2 TREES ARE CONNECTED" << '\n';
            reached=true;
            //std::cout << "closest node to connected_node=" << tree1.getNodeAt(tree1.getClosest(tree2.getNodeAt(vecteur_point[1]) )).getPoint() <<'\n';
            connected_node=tree1.getNodeAt(vecteur_point[0]);
            connected_node2=tree2.getNodeAt(vecteur_point[1]);
            std::cout << "connected node tree1 ="<< connected_node.getPoint() << '\n';
            std::cout << "connected node tree2 ="<< connected_node2.getPoint() << '\n';
            connected_node.setKey(vecteur_point[0]);
            connected_node2.setKey(vecteur_point[1]);

        }
        i++;
    }//fin while

    //affiche les noeuds de début et de fin

    circle(image, node1.getPoint(),5, Scalar(0,0,255),-1);
    circle(image, node_final.getPoint(),5, Scalar(0,255,0),-1);
    circle(image, connected_node.getPoint(),5, Scalar(0,255,125),-1);
    circle(image, connected_node2.getPoint(),5, Scalar(122,255,0),-1);

    imshow( "Display window", image );
    //std::cout << "tree1" <<'\n'<<'\n';
    //tree1.afficher_liste_noeuds_linked();
    //std::cout << "tree2" << '\n'<<'\n'<<'\n';
    //tree2.afficher_liste_noeuds_linked();



    tree1.drawPoint(image);
    waitKey(0);
    std::vector<int> indices, indices2;
    tree1.chemin(indices, node1, connected_node);
    tree2.chemin(indices2, node_final, connected_node2);

    waitKey(0);
    //tree1.affiche_vect(indices);
    //tree2.affiche_vect(indices2);

    std::vector<cv::Point> vecteurDePoint=tree1.do_list_point(tree2, indices, indices2);
    //vecteur contenant tous les points du chemin
    tree1.affichePoint(vecteurDePoint);
    tree1.afficher_chemin(indices);
    tree2.afficher_chemin(indices2);

    tree1.draw_pathway(image, indices) ;
    tree2.draw_pathway(image, indices2) ;
    //tree1.drawEachPoint(vecteurDePoint, image);
    imshow( "Display window", image );
    waitKey(0);
    /**********************************************************/



//              ROS

    void Callback(const geometry_msgs::PoseStamped& autorisation );



    ros::init(argc, argv, "ros_node_position");
    ros::init(argc, argv, "listener");

    ros::Publisher pos_pub_;
    ros::Subscriber autorisation_sub_;
    ros::NodeHandle nh_;
    geometry_msgs::Point point;
    geometry_msgs::PoseStamped pointstamped;

    //autorisation_sub_ = n.subscribe("Autorisation_node", 1, Callback);

    int taille=vecteurDePoint.size();
    for (int i = 0; i < taille; i++) {
        point.x=vecteurDePoint[i].x;
        point.y=vecteurDePoint[i].y;
        pointstamped.pose.position =point;
        pointstamped.header.frame_id = "map";
        pos_pub_ = nh_.advertise<geometry_msgs::PoseStamped>("/position", taille );
        pos_pub_.publish(pointstamped);
    }

    ros::spin();

    return 0;
}

/*******************************************************************************/
//charge image
int loadimage(char* chemin){

  image = imread(chemin , CV_LOAD_IMAGE_COLOR);   // Read the file
  cvtColor(image, img_grey,COLOR_BGR2GRAY); //On passe l'image en niveau de gris
  threshold(img_grey, img_bin,210,250,THRESH_BINARY_INV);

  width=image.size().width;
  height=image.size().height;
  int val=int(img_bin.at<uchar>(Point(200,200)) );
  std::cout << "val=" << val<< '\n';

  return 0;

}

/********************************************************************************/
