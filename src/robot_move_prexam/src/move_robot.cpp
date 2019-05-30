
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <sstream>

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "talker");

  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  ros::Rate loop_rate(10);

 
 //  * A count of how many messages we have sent. This is used to create
 // * a unique string for each message.
   
  int count = 0;
  while (ros::ok())
{
    geometry_msgs::Twist move;
    move.linear.x=3;
    move.angular.z=3; 

    pub.publish(move);

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
} 


//------------Publishing Float Messages---------------------

/*
#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include <stdio.h>
#include <sstream>
#include <iostream>
#include "std_msgs/String.h"



int main(int argc, char **argv)
{

ros::init(argc, argv, "talker");

ros::NodeHandle n;

ros::Publisher pub = n.advertise<std_msgs::Float32>("/cmd_vel", 1000);

ros::Rate loop_rate(10);

int count = 0;
while (ros::ok())
{

std_msgs::Float32 msg;

msg.data.x = 15.0;
msg.data.y = 16.0;c

pub.publish(msg);

//ROS_INFO("%s", msg.data.c_str());
ROS_INFO("%s", msg.data);

ros::spinOnce();

loop_rate.sleep();

++count;
}

return 0;
} */
