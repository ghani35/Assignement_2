//you can run this node by  " rosrun my_srv server " 
//this is a node that calculates the function preformed by the server

#include "ros/ros.h"
#include "my_srv/Velocity.h"


bool myrandom (my_srv::Velocity::Request &req, my_srv::Velocity::Response &res){
if(req.input==2.0){
res.y= req.x/1.5;
}
if(req.input==3.0){
res.y= req.x*1.5;
}

return true;
}

int main(int argc, char **argv)
{
ros::init(argc, argv, "server");
ros::NodeHandle n;
ros::ServiceServer service= n.advertiseService("/velocity",myrandom);
ros::spin();
return 0;
}
