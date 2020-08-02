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
   service_bool = true;
  }else{
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
  ros::init(argc, argv, "Service_server_ninja");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("Service_server_ninja", Service_callback);

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