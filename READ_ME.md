PROJET ROBOTIQUE MOBILE :

Lancer tout :

COMMANDES A LANCER :  roslaunch projet_rob_mob projet_rob_mob.launch

Simu gazebo : minilab_simulation minilab_simulation.launch

joy : rosrun joy joy_node
Teleop : rosrun my_teleop my_teleop
Création de map : rosrun map_server map_saver -f ~/ROB_MOB/maps/my_map.pgm
Gmapping: rosrun gmapping slam_gmapping
