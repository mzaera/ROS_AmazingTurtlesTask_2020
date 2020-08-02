#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <std_srvs/SetBool.h>


class Turtle_Srv
{
private:

    ros::NodeHandle n;
    ros::Subscriber sub;
    ros::Publisher cmd_vel_pub;
    ros::ServiceServer service;

    geometry_msgs::Twist guardat;
    geometry_msgs::Twist msg;

    bool service_bool;
      

public:
    Turtle_Srv()
    {
        this->n = ros::NodeHandle();
        this->sub = n.subscribe("keyboard/cmd_vel", 1000, &Turtle_Srv::Move_callback, this );
        this->cmd_vel_pub =  n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
        this->service = n.advertiseService("ninja_service", &Turtle_Srv::Service_callback, this);
        ros::Duration(1).sleep();
    }

    void run(){

        ros::Rate loop_rate(100);

        while (ros::ok())
        {
          if(this->service_bool){
            this->cmd_vel_pub.publish(this->guardat);
          }


            ros::spinOnce();
            loop_rate.sleep();
        }
    }

    bool Service_callback(std_srvs::SetBool::Request& request, std_srvs::SetBool::Response& response)
    {
      if(request.data){
        response.success = true;
        response.message="You can use teleop_twist_keyboard";
        this->service_bool = true;
      }else{
        response.success = true;
        response.message="You can not use teleop_twist_keyboard";
        this->service_bool = false ;
      }

      return true;
    }

    void Move_callback(const geometry_msgs::Twist rebut)
    {
      this->guardat=rebut;
    }

};


int main(int argc, char **argv){

    ros::init(argc, argv, "ninja_service");

    auto controller = Turtle_Srv();
    controller.run();

    return 0;
}










