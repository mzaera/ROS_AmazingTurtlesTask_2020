#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include <std_srvs/SetBool.h>
#include <cstdlib>



auto msg = geometry_msgs::Twist();

int main(int argc, char **argv){

    ros::init(argc, argv,"ninja_controller");


    ros::NodeHandle n;
    ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    
    ros::Rate loop_rate(10);

    ros::ServiceClient client = n.serviceClient<std_srvs::SetBool>("ninja_controller");
    std_srvs::SetBool srv;


    bool test = true;

    while (ros::ok())
    {

        test=client.call(srv);
        
        if(test){

             ROS_INFO(" funcionaaaaaaa!!!!!!!!!!");

        }else{
               //ROS_INFO(" nidea");
          
        }

        ros::spinOnce();
        loop_rate.sleep();
    }



    return 0;
}
