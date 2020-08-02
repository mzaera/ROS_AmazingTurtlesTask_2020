#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"

#define PI 3.1415926535898

class Turtle_Triangle
{
private:

    ros::NodeHandle n;
    ros::Subscriber sub;
    ros::Publisher cmd_vel_pub;

    turtlesim::Pose actual_pose;
    geometry_msgs::Twist msg;

    int part = 0;
      

public:
    Turtle_Triangle()
    {
        this->n = ros::NodeHandle();
        this->sub = n.subscribe("turtle1/pose", 1000, &Turtle_Triangle::pose_Callback, this );
        this->cmd_vel_pub =  n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
        ros::Duration(1).sleep();
    }

    void run(){

        ros::Rate loop_rate(100);

        while (ros::ok())
        {

            this->triangle();
            this->cmd_vel_pub.publish(this->msg);

            ros::spinOnce();
            loop_rate.sleep();
        }
    }

    void pose_Callback(const turtlesim::PoseConstPtr& pose)
    {
        this->actual_pose.theta = pose->theta;
        this->actual_pose.x = pose->x;
        this->actual_pose.y = pose->y;
    }

    void triangle(){
        switch(this->part){

            case 0:

                if(this->actual_pose.x<=8.0 ){
                    this->msg.linear.x = 1.0;
                    this->msg.angular.z = 0.0;
                }else{
                    this->part++;
                }
            break;

            case 1:
                if ( this->actual_pose.theta < 2.35619449){
                    this->msg.linear.x = 0.0;
                    this->msg.angular.z = 1.0;
                } else {
                    this->part++;
                }                
            break;

            case 2:
                if ( this->actual_pose.x > 5.544445){
                    this->msg.linear.x = 1.0;
                    this->msg.angular.z = 0.0;
                } else {
                    this->part++;
                }                
            break;

            case 3:
                if ( this->actual_pose.theta > 0){
                    this->msg.linear.x = 0.0;
                    this->msg.angular.z = 1.0;
                } else {
                    this->part++;
                }                
            break;

            case 4:
                if ( this->actual_pose.theta < (-PI/2) ){
                    this->msg.linear.x = 0.0;
                    this->msg.angular.z = 1.0;
                } else {
                    this->part++;
                }            
            break;

            case 5:
                if ( this->actual_pose.y > 5.544445 ){
                    this->msg.linear.x = 1.0;
                    this->msg.angular.z = 0.0;
                } else {
                    this->part++;
                }            
            break;

            case 6:
                if ( this->actual_pose.theta < 0 ){
                    this->msg.linear.x = 0.0;
                    this->msg.angular.z = 1.0;
                } else {
                    this->part=0;
                }            
            break;

        }

    }

};


int main(int argc, char **argv){

    ros::init(argc, argv, "normal_Part2");

    auto controller = Turtle_Triangle();
    controller.run();

    return 0;
}