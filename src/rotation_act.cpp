#include <iostream>
#include <stdlib.h>     
#include "ros/ros.h"

#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

#include <std_srvs/SetBool.h>


/*--------------------------------------------------Object part-------------------------------------------*/

class Turtle{
private:

    ros::NodeHandle nh;
    ros::Publisher cmd_vel_pub;

    geometry_msgs::Twist msg;

public:
    Turtle()
    {
        this->nh = ros::NodeHandle();
        this->cmd_vel_pub =  nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);

        ros::Duration(0.1).sleep();
    }

    void run(){

        ros::Rate loop_rate(10);
        while (ros::ok())
        {
            this->msg.linear.x = 1.0;
            this->msg.angular.z = 1.0;

            this->cmd_vel_pub.publish(this->msg);

            ros::spinOnce();
            loop_rate.sleep();
        }
    }

};      



/*------------------------------------------Not more in object part--------------------------------------*/

int main(int argc, char **argv){

    ros::init(argc, argv, "rotation_act");

    auto player = Turtle();
    player.run();


    return 0;
}