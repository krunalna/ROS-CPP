#include<ros/ros.h>
#include<std_msgs/Int32.h>
#include<nav_msgs/Odometry.h>

void odomCallback( const nav_msgs::Odometry::ConstPtr& msg)
{
    ROS_INFO("%f", msg->pose.pose.position.x);
    ROS_INFO("%f", msg->pose.pose.position.y);
    ROS_INFO("%f", msg->pose.pose.orientation.z);
    //ROS_INFO("%d", msg->pose.pose.position.y);
    //ROS_INFO("%d", msg->pose.pose.position.x);
    //ROS_INFO("%d", msg->pose.pose.position.y);

}

int main(int argc, char** argv) {

ros::init(argc, argv,"odom_topic_subscriber");
ros::NodeHandle nh;

ros::Subscriber sub = nh.subscribe("odom", 1000, odomCallback);

ros::spin();

return 0;
}