#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include <iostream>


void turtleCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
int i1=300;
int i2=360;
int i3=180;
int i4=420;
int i5=0;
int i6=540;

float min1,min2,min3,min4,min5,min6;
min1=msg->ranges[300];
min2=msg->ranges[360];
min3=msg->ranges[180];
min4=msg->ranges[420];
min5=msg->ranges[0];
min6=msg->ranges[540];

for(  i1 =300; i1 < 360; i1++){

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
        
        
        
        printf("min1 = %f \n",min1);
        printf("min2 = %f \n",min2);
        printf("min3 = %f \n",min3);
        printf("min4 = %f \n",min4);
        printf("min5 = %f \n",min5);
        printf("min6 = %f \n",min6);
        printf("\n");
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "sub_code");
   ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("base_scan", 10, turtleCallback);
    ros::spin();
    return 0;
}

