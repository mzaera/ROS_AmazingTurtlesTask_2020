#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"


#define PI 3.1415926535898

turtlesim::Pose actual_pose;

void poseCallback(const turtlesim::PoseConstPtr& pose)
{
    actual_pose.theta = pose->theta;
    actual_pose.x = pose->x;
    actual_pose.y = pose->y;

    ROS_INFO("x: [%f] y: [%f] theta: [%f] ",actual_pose.x, actual_pose.y, actual_pose.theta);

}

int main(int argc, char **argv){

    ros::init(argc, argv,"normal3");

    ros::NodeHandle n;
    ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    ros::Subscriber sub = n.subscribe("turtle1/pose", 1000, poseCallback);
    ros::Rate loop_rate(10);

    auto msg = geometry_msgs::Twist();

    while (ros::ok())
    {

        msg.linear.x = 1.0;
        msg.angular.z = 1.0;
        cmd_vel_pub.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
