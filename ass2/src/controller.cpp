#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "ass2/User.h"    // header of costumized message
#include <iostream>
#include "geometry_msgs/Twist.h"
#include <sstream>
#include "std_srvs/Empty.h" //header of reset_position service
#include "my_srv/Velocity.h" // header of costumized service 

int input; 
// input is used to save the data entred by the user 
float x;
//x used as a velocity multiplier to control it 
ros::Publisher pub;
// publisher that publish the velocity to the robot	 
ros::ServiceClient client1; 
std_srvs::Empty srv1;
ros::ServiceClient client2;
my_srv::Velocity srv2;

void user_input(const ass2::User::ConstPtr& msg)
{
 input= msg->user;  
}
//this function used to returne the data entred by the user through a costumized message 



void robotCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{

printf("the user entered   %d  ", input);
printf("    the speed multiplier x=  %f \n", x);

// this variable are used to declare the initial index of each range  
int i1=300;
int i2=360;
int i3=180;
int i4=420;
int i5=0;
int i6=540;

//the min is used to returne the most closest obstacl in eache range 
float min1,min2,min3,min4,min5,min6;
min1=msg->ranges[300];
min2=msg->ranges[360];
min3=msg->ranges[180];
min4=msg->ranges[420];
min5=msg->ranges[0];
min6=msg->ranges[540];

for( i1 =300; i1 < 360; i1++){

         if(msg->ranges[i1] < min1){    
            min1 = msg->ranges[i1];
        } 
        }
for( i2 =360; i2 < 420; i2++){

         if(msg->ranges[i2] < min2){
            min2 = msg->ranges[i2];
        } 
        }
for( i3 =180; i3 < 300; i3++){

         if(msg->ranges[i3] < min3){
            min3 = msg->ranges[i3];
        } 
        }
for( i4 =420; i4 < 540; i4++){

         if(msg->ranges[i4] < min4){
            min4 = msg->ranges[i4];
        } 
        }
for( i5 =0; i5 < 180; i5++){

         if(msg->ranges[i5] < min5){
            min5 = msg->ranges[i5];
        } 
        }        
for( i6 =540; i6 < 720; i6++){

         if(msg->ranges[i6] < min6){
            min6 = msg->ranges[i6];
        } 
        }        
 
// if the user enters 2 the robot decreas the velocity
// if the user enters 3 the robot increase the velocity 
// this is done by our costumized service Velocity.srv
// the service Velocity.srv is defined in other package (my_srv)
// the function implemented by calling the Velocity.srv is written in src/server.cpp 
// the function implemented by this server is commanted in details in the directory my_srv/src/server.cpp
// so to use this server we must start it first

if(input == 2){
 srv2.request.input = input;
 srv2.request.x = x;
 client2.waitForExistence();
 client2.call(srv2);
  input=0;
 x= srv2.response.y;

}
    
if(input == 3){
 srv2.request.input = input;
 srv2.request.x = x;
 client2.waitForExistence();
 client2.call(srv2);
  input=0;
 x= srv2.response.y;

}       
 //if the user enters 1 the robot reset its position 
 // we used directly the server provided reset_position                            
if(input== 1.0){
 client1.call(srv1);
}    
// the angular velocity is INVERSLY proportional to linear velocity
geometry_msgs::Twist my_vel;
if(min1<0.6){
my_vel.linear.x = 0.0;
my_vel.angular.z = 10.0;
//printf(" 1 \n");
}
else if(min2<0.6){
my_vel.linear.x = 0.0;
my_vel.angular.z = -10.0;
//printf(" 2 \n");
}
else if(min3<0.6){
my_vel.linear.x = x*1.0;
my_vel.angular.z = 7.0/(3*x+2);
//printf(" 3 \n");
}
else if(min4<0.6){
my_vel.linear.x = x*1.0;
my_vel.angular.z = -7.0/(3*x+2);
//printf(" 4 \n");
}
else if(min5<0.6){
my_vel.linear.x = x*1.0;
my_vel.angular.z = 5.0/(3*x+1);
//printf(" 5 \n");
}
else if(min6<0.6){
my_vel.linear.x = x*1.0;
my_vel.angular.z = -5.0/(3*x);
//printf(" 6 \n");
}
else {
my_vel.linear.x = x*2.0;
my_vel.angular.z = 0.0;
//printf(" 7 \n");
}
pub.publish(my_vel);
}


int main (int argc, char **argv)
{
// initialize the velocity multiplier to 1.0
x=1.0;
ros::init(argc, argv, "pubsub");
ros::NodeHandle nh;
ros::Subscriber sub = nh.subscribe("base_scan", 10, robotCallback);
ros::Subscriber sub_user = nh.subscribe("user_topic", 10, user_input);
pub = nh.advertise<geometry_msgs::Twist> ("/cmd_vel", 1); 
 
client1 =  nh.serviceClient<std_srvs::Empty>("/reset_positions");
client2 =  nh.serviceClient<my_srv::Velocity>("/velocity");


 
ros::spin();

return 0;
}
