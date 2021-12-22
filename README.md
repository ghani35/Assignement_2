# Decription of the program
* USED PACKAGES: 
   1-second_assignement
   2-my_srv
   3-ass2
* USED NODES:
   server : it is located in my_srv/src/server.cpp
            used to implement the function used by the customited server. 
            the function is to return the speed multiplier either incremented or decremented, dependig on the user request 
   controller_node : it is located in ass2/src/controller.cpp 
                     used to control the robot
   ui_node : it is located in ass2/src/ui.cpp
             used as user interface to allow the user to enter the commands
   stage_ros : provided by second assignement package 
              used to run the 2D simulator
* CUSTOMITED SERVICE:
   created in my_srv/srv/Velocity.srv
   has two float32 requests and one float32 response 
   the two requestes are : the user input  and the current velocity of the robot
   the response : the new velocity multiplier assigned to the robot
* CUSTOMITED MESSAGE:
   created in ass2/msg/User.msg
   has one argument  int32 
   used to transfer the data entred by the user to be used by the controller program
# How to run it 
1- run the 2D simulator by   "rosrun stage_ros stageros $(rospack find second_assignment)/world/my_world.world"
2- run the server by  "rosrun my_srv server "
3- run the user interface by "rosrun ass2 ui_node"
4- run the controller node by " rosrun ass2 controller "
# How to use the user interface 
the user need to enter integer numbers to control the robot.
enter 1 to reset
enter 2 to slowdown
enter 3 to speedup
# PSEUDO_CODE OF THE CONTROLLER.CPP 
headers
declare the publisher and services 
declare user_input() 
    // it is a function used to return the value of the integer entred by the user
declare robotCalback()
    initialize integer variables to starting index for each range (i used 6 ranges ) i1...i6
    initialize a float to stor the minnimum value returned by eache range (min1 .. min6)
    if(the user enter 1) {call the reset_position service }
    if(the user enter 1) {call the customited service }
    if(the user enter 3) {call the customited service }
    publish a specific angular and linear velocity for each range 
int main()
    intialize publisher and clients
