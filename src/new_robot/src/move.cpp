#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

#include <sstream>

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);

  ros::Rate loop_rate(10);

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;
  while (ros::ok())
{
    geometry_msgs::Twist move;
    move.angular.z=3;

    pub.publish(move);

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}
