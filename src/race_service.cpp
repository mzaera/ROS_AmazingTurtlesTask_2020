#include <iostream>
#include "ros/ros.h"

#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

#include "turtlesim/Pose.h"
#include "turtlesim/Spawn.h"
#include "turtlesim/TeleportAbsolute.h"
#include "turtlesim/Kill.h"

#include <std_srvs/SetBool.h>


class Turtle_Srv
{
private:

    ros::NodeHandle n;
    ros::Subscriber sub;
    ros::Publisher cmd_vel_pub;
    ros::ServiceServer service;

    geometry_msgs::Twist msg;

    bool service_bool;
      

public:
    Turtle_Srv()
    {
        this->n = ros::NodeHandle();
        this->cmd_vel_pub =  n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
        this->service = n.advertiseService("ninja_service", &Turtle_Srv::Service_callback, this);
        

        ros::Duration(0.2).sleep();
        this->kill("turtle1");
        this->spawn_turtle(1.0,7.5,"player1");
        this->spawn_turtle(1.0,5.0,"player2");

        ros::Duration(1).sleep();
    }

    void run(){

        ros::Rate loop_rate(100);

        while (ros::ok())
        {
          if(this->service_bool){
            this->cmd_vel_pub.publish(this->msg);
          }
            ros::spinOnce();
            loop_rate.sleep();
        }
    }

    void spawn_turtle(float x, float y, std::string turtle_name){

        ros::ServiceClient client = n.serviceClient<turtlesim::Spawn>("spawn");
        turtlesim::Spawn srv;

        srv.request.x = x;
        srv.request.y = y;
        srv.request.theta = 0;
        srv.request.name = turtle_name;

        client.call(srv);
    }


    void kill(std::string turtle_name){

        ros::ServiceClient client = n.serviceClient<turtlesim::Kill>("kill");
        turtlesim::Kill srv;

        srv.request.name = turtle_name ;

        client.call(srv);
    }

    bool Service_callback(std_srvs::SetBool::Request& request, std_srvs::SetBool::Response& response)
    {
      if(request.data){
        response.success = true;
        response.message="RACE STARTS!!!!!";
        this->service_bool = true;
      }else{
        response.success = true;
        response.message="RACE STOPED";
        this->service_bool = false ;
      }

      return true;
    }

};


int main(int argc, char **argv){

    ros::init(argc, argv, "race_service");

    auto controller = Turtle_Srv();
    controller.run();

    return 0;
}










