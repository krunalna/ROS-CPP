#include "ros/node_handle.h"
#include "ros/publisher.h"
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Int32.h>
#include<string>

//ros::Publisher pub;

void scanCallback(const sensor_msgs::LaserScan::ConstPtr &msg) {
  float front = msg->ranges[360];
  float right = msg->ranges[0];
  float left = msg->ranges[719];
  ROS_INFO("%f", front);
  ROS_INFO("%s", "Hello!, from callback");

  ros::NodeHandle ph;
  ros::Publisher pub = ph.advertise<geometry_msgs::Twist>("cmd_vel", 1);
  geometry_msgs::Twist velocity;

  //velocity.linear.x = 0.2;

  float linear_X, angular_Z;
  linear_X = 0.0;
  angular_Z = 0.0;

  if (front <= 1.0){
    linear_X = 0;
    angular_Z = 0.5;
  }
  else {
  linear_X = 0.3;
  }


  velocity.linear.x = linear_X;
  velocity.angular.z = angular_Z;

  pub.publish(velocity);
  //ros::spinOnce();
  ROS_INFO("%s", "Bye......");
  
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "topics_quiz_node");
  ros::NodeHandle nh;

  // ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  ros::Subscriber sub = nh.subscribe("/kobuki/laser/scan", 1, scanCallback);

  ros::spin();

  return 0;
}
