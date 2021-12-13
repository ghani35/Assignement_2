//you can run this node by  " rosrun ass2 ui_node  " 
//this node is used to publish a msg enred by the user to control the robot
//the message used is ass2/msg/User.msg

#include "ros/ros.h"
#include "ass2/User.h"
#include <sstream>





int main (int argc, char **argv)
{
int num;
// Initialize the node, setup the NodeHandle for handling the communication with the ROS
//system
ros::init(argc, argv, "User_node");
ros::NodeHandle nh;
// Define the subscriber to turtle's position

ros::Publisher pub = nh.advertise<ass2::User> ("user_topic", 1); 
ros::Rate loop_rate(10);

while (ros::ok()){

ass2::User input;
std::cout << "Enter (1) to reset || (2) to decreas || (3) to increace  : ";
 std :: cin >> num;

input.user = num;

pub.publish(input);
sleep(1);
//the sleep is used to give enough time for the message to be used
//befor putting it again to 0

input.user = 0;
pub.publish(input);
ros::spinOnce();



loop_rate.sleep();

}

return 0;
}


















/* #include <iostream>
using namespace std;

int main()
{


	int num;

	// Input the integer
	cout << "Enter the integer: ";
	cin >> num;

	// Display the integer
	cout << "Entered integer is: " << num;

	return 0;
}
*/
