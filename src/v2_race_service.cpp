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
    
    geometry_msgs::Twist msg;

      

public:
    Turtle()
    {
        this->nh = ros::NodeHandle();
        this->cmd_vel =  nh.advertise<geometry_msgs::Twist>("player1/cmd_vel", 1000);
        
        ros::Duration(0.1).sleep();
    }

};  



/*------------------------------------------Not more in object part--------------------------------------*/

bool service_bool = false;

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


int main(int argc, char **argv){

    ros::init(argc, argv, "v2_race_service");
    ros::NodeHandle n;

    ros::ServiceServer service= n.advertiseService("v2_race_service", Service_callback);

    auto player1 = Turtle();
    auto player2 = Turtle();

    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        if(service_bool){




        }

        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}