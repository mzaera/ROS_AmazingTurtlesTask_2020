#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

#include <std_srvs/SetBool.h>


bool callback(std_srvs::SetBool::Request& request, std_srvs::SetBool::Response& response)
{

  if(request.data){
    ROS_INFO(" trueeeee !!!!!!!");
    response.success = true;
  }else{
    ROS_INFO(" false !!!!!!!");
    response.success = true;
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