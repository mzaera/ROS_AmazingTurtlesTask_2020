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

/*--------------------------------------------------Object part-------------------------------------------*/

class Turtle{
private:

    ros::NodeHandle nh;
    ros::Publisher cmd_vel;
    ros::Subscriber sub;

    turtlesim::Pose actual_pose;

public:
    Turtle(std::string sub_topic, std::string pub_topic)
    {
        this->nh = ros::NodeHandle();

        this->sub = nh.subscribe(sub_topic, 1000, &Turtle::pose_Callback, this );
        this->cmd_vel =  nh.advertise<geometry_msgs::Twist>(pub_topic, 1000);

        ros::Duration(0.1).sleep();
    }

    void pose_Callback(const turtlesim::PoseConstPtr& pose){
        this->actual_pose.x = pose->x;
    }

    void run(){



    }

};  



/*------------------------------------------Not more in object part--------------------------------------*/

bool service_bool = false;
bool start = true;
bool need_to_kill;

bool Service_callback(std_srvs::SetBool::Request& request, std_srvs::SetBool::Response& response)
{
    if(request.data){
        response.success = true;
        response.message="SERVICE STARTS";
        service_bool = true;
    }else{
        response.success = true;
        response.message="SERVICE STOPS";
        service_bool = false ;
      }

    return true;
}

void kill(std::string turtle_name){
    ros::NodeHandle n_tokill;
    ros::ServiceClient client = n_tokill.serviceClient<turtlesim::Kill>("kill");
    turtlesim::Kill srv;
    srv.request.name = turtle_name ;
    client.call(srv);
}

void spawn(float x, float y, std::string turtle_name){
    ros::NodeHandle n_tospawn;
    ros::ServiceClient client = n_tospawn.serviceClient<turtlesim::Spawn>("spawn");
    turtlesim::Spawn srv;
    srv.request.x = x;
    srv.request.y = y;
    srv.request.theta = 0;
    srv.request.name = turtle_name;

    client.call(srv);
    }


int main(int argc, char **argv){

    ros::init(argc, argv, "v2_race_service");
    ros::NodeHandle n;

    ros::ServiceServer service= n.advertiseService("v2_race_service", Service_callback);

    auto player1 = Turtle("player1/pose", "player1/cmd_vel");
    auto player2 = Turtle("player2/pose", "player2/cmd_vel");


    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        if(service_bool){
            if (start){
                kill("turtle1");
                spawn(1.0,7.5,"player1");
                spawn(1.0,5.0,"player2");
                start = false;
                need_to_kill = true;
            }

            player1.run();
            player2.run();


        }else if (need_to_kill){
            kill("player1");
            kill("player2");
            spawn(5.544445,5.544445,"turtle1");
            start = true;
            need_to_kill = false;

        }

        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}