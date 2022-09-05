#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

float linX, angZ;

void counterCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  ROS_INFO("%f", msg->ranges[360]); //We print the distance to an obstacle in front of the robot
  
  //If the distance to an obstacle in front of the robot is bigger than 1 meter, the robot will move forward
  if (msg->ranges[360] > 1)
  {
    linX = 0.1;
    angZ = 0.0;
  }
  //If the distance to an obstacle in front of the robot is smaller than 1 meter, the robot will turn left
  if (msg->ranges[360] < 1)
  {
    linX = 0.0;
    angZ = 0.2;
  }
  //If the distance to an obstacle at the left side of the robot is smaller than 0.3 meters, the robot will turn right
  if (msg->ranges[719] < 1)
  {
    linX = 0.0;
    angZ = -0.2;
  }
  //If the distance to an obstacle at the right side of the robot is smaller than 0.3 meters, the robot will turn left
  if (msg->ranges[0] < 1)
  {
    linX = 0.0;
    angZ = 0.2;
  }
  
}

int main(int argc, char** argv) {

    ros::init(argc, argv, "topics_quiz_node");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/kobuki/laser/scan", 1000, counterCallback); //We subscribe to laser's topic
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    geometry_msgs::Twist move;
    
    ros::Rate rate(2);

    while(ros::ok()){
      
      move.linear.x = linX;
      move.angular.z = angZ;
      pub.publish(move);
      
      rate.sleep();
      ros::spinOnce();
      
    }
    
    return 0;
}