#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <sstream>





int main (int argc, char **argv)
{
// Initialize the node, setup the NodeHandle for handling the communication with the ROS
//system
ros::init(argc, argv, "pub_code_name");
ros::NodeHandle nh;
// Define the subscriber to turtle's position

ros::Publisher pub = nh.advertise<geometry_msgs::Twist> ("/cmd_vel", 1); 
ros::Rate loop_rate(10);

while (ros::ok()){

geometry_msgs::Twist my_vel;
my_vel.linear.x = 2.0;
my_vel.angular.z = 0.02;
pub.publish(my_vel);

ros::spinOnce();
loop_rate.sleep();
}

return 0;
}
