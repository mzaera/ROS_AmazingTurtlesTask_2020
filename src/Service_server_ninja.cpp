#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

#include <std_srvs/SetBool.h>


bool callback(std_srvs::SetBool::Request& request, std_srvs::SetBool::Response& response)
{

    ros::NodeHandle nh;
    ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    ros::Publisher bool_pub = nh.advertise<std_msgs::String>("bool_topic", 1000);
    
    ros::Rate loop_rate(10);
    ros::Time start_time = ros::Time::now();
    ros::Duration transcorregut = ros::Time::now() - start_time;
    ros::Duration periode(5.0); 

    auto msg = geometry_msgs::Twist();
    std_msgs::String test_num522;

  if(request.data){
    ROS_INFO(" trueeeee !!!!!!!");
    response.success = true;

    msg.linear.x = 1.0;
    msg.angular.z = 1.0;

    test_num522.data= "TRUE";

  }else{
    ROS_INFO(" false !!!!!!!");
    response.success = false; 

    msg.linear.x = 0.0;
    msg.angular.z = 0.0;   

    test_num522.data= "FALSE";

  }

  while(transcorregut < periode){
    
    transcorregut = ros::Time::now() - start_time;

    cmd_vel_pub.publish(msg);
    bool_pub.publish(test_num522);

    loop_rate.sleep();
  }


  return true;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "Service_server_ninja");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("Service_server_ninja", callback);

  ros::spin();

  return 0;
}