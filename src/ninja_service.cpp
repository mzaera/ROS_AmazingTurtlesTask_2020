#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

#include <std_srvs/SetBool.h>

bool service_bool;
geometry_msgs::Twist guardat;

bool Service_callback(std_srvs::SetBool::Request& request, std_srvs::SetBool::Response& response)
{
  if(request.data){
    response.success = true;
    response.message="You can use teleop_twist_keyboard";
    service_bool = true;
  }else{
    response.success = true;
    response.message="You can not use teleop_twist_keyboard";
    service_bool = false ;
  }

  return true;
}


void Move_callback(const geometry_msgs::Twist rebut)
{
  guardat=rebut;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "ninja_service");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("ninja_service", Service_callback);

  ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
  auto msg = geometry_msgs::Twist();

  ros::Subscriber sub = n.subscribe("keyboard/cmd_vel", 1000, Move_callback);

  ros::Rate loop_rate(10);

  while (ros::ok())
  {

    if(service_bool){
      cmd_vel_pub.publish(guardat);
    }

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}