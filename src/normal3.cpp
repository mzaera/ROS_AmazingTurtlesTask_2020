#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"


#define PI 3.1415926535898

int part = 0;
turtlesim::Pose actual_pose;
auto msg = geometry_msgs::Twist();


void poseCallback(const turtlesim::PoseConstPtr& pose)
{
    actual_pose.theta = pose->theta;
    actual_pose.x = pose->x;
    actual_pose.y = pose->y;

}

void triangle(){
    switch(part){

        case 0:

            if(actual_pose.x<=8.0 ){
                msg.linear.x = 1.0;
                msg.angular.z = 0.0;
            }else{
                part++;
            }
        break;

        case 1:
            if ( actual_pose.theta < 2.35619449){
                msg.linear.x = 0.0;
                msg.angular.z = 1.0;
            } else {
                part++;
            }                
        break;

        case 2:
            if ( actual_pose.x > 5.544445){
                msg.linear.x = 1.0;
                msg.angular.z = 0.0;
            } else {
                part++;
            }                
        break;

        case 3:
            if ( actual_pose.theta > 0){
                msg.linear.x = 0.0;
                msg.angular.z = 1.0;
            } else {
                part++;
            }                
        break;

        case 4:
            if ( actual_pose.theta < (-PI/2) ){
                msg.linear.x = 0.0;
                msg.angular.z = 1.0;
            } else {
                part++;
            }            
        break;

        case 5:
            if ( actual_pose.y > 5.544445 ){
                msg.linear.x = 1.0;
                msg.angular.z = 0.0;
            } else {
                part++;
            }            
        break;

        case 6:
            if ( actual_pose.theta < 0 ){
                msg.linear.x = 0.0;
                msg.angular.z = 1.0;
            } else {
                part=0;
            }            
        break;

    }

}

int main(int argc, char **argv){

    ros::init(argc, argv,"normal3");

    ros::NodeHandle n;
    ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    ros::Subscriber sub = n.subscribe("turtle1/pose", 1000, poseCallback);
    ros::Rate loop_rate(100);

    ros::Duration(1).sleep();


    while (ros::ok())
    {

        
        triangle();

        cmd_vel_pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
