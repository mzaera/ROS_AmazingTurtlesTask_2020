#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include <std_srvs/SetBool.h>
#include <cstdlib>

bool final=false;
geometry_msgs::Twist rebut_gen;

void move(const geometry_msgs::Twist rebut)
{
rebut_gen=rebut;
}



void detect(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("I heard: [%s]", msg->data.c_str());

    std_msgs::String resp;
    resp.data = msg->data.c_str();

    if(resp.data=="TRUE"){
        final=true;
    }else if (resp.data=="FALSE"){
        final=false;
    }

}


int main(int argc, char **argv){

    ros::init(argc, argv,"ninja_controller");

    ros::NodeHandle n;

    ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
    auto msg = geometry_msgs::Twist();

    ros::Subscriber sub = n.subscribe("bool_topic", 1000,detect);
    ros::Subscriber sub2 = n.subscribe("keyboard/cmd_vel", 1000, move);

    ros::Rate loop_rate(10);

    while (ros::ok())
    {
        if(final){
            //msg.linear.x = 1.0;
            //msg.angular.z = 1.0;
            //cmd_vel_pub.publish(msg);
            cmd_vel_pub.publish(rebut_gen);

        }else{
            msg.linear.x = 0.0;
            msg.angular.z = 0.0;  
            cmd_vel_pub.publish(msg);

        }



        ros::spinOnce();
        loop_rate.sleep();
    }



    return 0;
}
