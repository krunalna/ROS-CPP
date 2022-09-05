#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include<geometry_msgs/Twist.h>

int main(int argc, char** argv) {

    ros::init(argc, argv, "cmd_vel_publisher");
    ros::NodeHandle nh;
    
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    ros::Rate loop_rate(2);
    
    //std_msgs::Int32 count;
    //count.data = 0;
    geometry_msgs::Twist velocity;

    velocity.linear.x = 0.0; //0.5
    velocity.angular.z = 0.0; //0.5
    
    while (ros::ok())
    {
        pub.publish(velocity);
        ros::spinOnce();
        loop_rate.sleep();
        //++count.data;
    }
    
    return 0;
}
