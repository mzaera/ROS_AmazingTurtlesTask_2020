#include <iostream>
#include <stdlib.h>     
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
    ros::Subscriber sub2;

    ros::Publisher cmd_vel_player1;
    ros::Publisher cmd_vel_player2;

    ros::ServiceServer service;

    turtlesim::Pose player1_actual_pose;
    turtlesim::Pose player2_actual_pose;



    geometry_msgs::Twist msg;

    bool service_bool;
    int part;


      

public:
    Turtle_Srv()
    {
        this->n = ros::NodeHandle();
        this->cmd_vel_player1 =  n.advertise<geometry_msgs::Twist>("player1/cmd_vel", 1000);
        this->cmd_vel_player2 =  n.advertise<geometry_msgs::Twist>("player2/cmd_vel", 1000);
        this->service = n.advertiseService("race_service", &Turtle_Srv::Service_callback, this);
        
        this->sub = n.subscribe("player1/pose", 1000, &Turtle_Srv::pose_Callback_player1, this );
        this->sub2 = n.subscribe("player2/pose", 1000, &Turtle_Srv::pose_Callback_player2, this );

        ros::Duration(0.2).sleep();

        this->kill("turtle1");
        this->spawn_turtle(1.0,7.5,"player1");
        this->spawn_turtle(1.0,5.0,"player2");

        ros::Duration(0.2).sleep();
    }

    void run(){

        ros::Rate loop_rate(10);

        while (ros::ok())
        {

            if(this->service_bool){

                this->race();

            }else{
                this->part=0;
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

    float RandomFloat(float a, float b) {
        float random = ((float) rand()) / (float) RAND_MAX;
        float diff = b - a;
        float r = random * diff;
        return a + r;
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

    void pose_Callback_player1(const turtlesim::PoseConstPtr& pose){
        this->player1_actual_pose.x = pose->x;
    }

    void pose_Callback_player2(const turtlesim::PoseConstPtr& pose){
        this->player2_actual_pose.x = pose->x;
    }

    void race(){

        switch(this->part){

            case 0:
                this->kill("player1");
                this->kill("player2");                
                this->spawn_turtle(1.0,7.5,"player1");
                this->spawn_turtle(1.0,5.0,"player2");
                ros::Duration(0.2).sleep();
                this->part++;
            break;

            case 1:
               // if(this->player1_actual_pose.x < 10 && this->player2_actual_pose.x < 10 ){
                    this->msg.linear.x = this->RandomFloat( 1.0, 2.5 );
                    this->cmd_vel_player1.publish(this->msg);
                    this->msg.linear.x = this->RandomFloat( 1.0, 2.5 );
                    this->cmd_vel_player2.publish(this->msg);
              //  }else{
                    this->part++;
               // }
            break;

            case 2:
                //this->service_bool=false;
            break;
        }
    }
};  


int main(int argc, char **argv){

    ros::init(argc, argv, "race_service");

    auto controller = Turtle_Srv();
    controller.run();

    return 0;
}










