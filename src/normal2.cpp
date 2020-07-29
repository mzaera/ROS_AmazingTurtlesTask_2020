#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"


class TurtleController
{
private:
    
    ros::Publisher cmd_vel_pub;
  	ros::NodeHandle n;


    geometry_msgs::Twist calculateCommand()
    {
        auto msg = geometry_msgs::Twist();
        msg.linear.x = 1.0;
        msg.angular.z = 0.0;
        return msg;
    }


public:
    TurtleController(){

        this->n = ros::NodeHandle();
   
        this->cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    }

    void run(){

        ros::Rate loop_rate(10);

        while (ros::ok())
        {

            auto msg = calculateCommand();
            this->cmd_vel_pub.publish(msg);





            ros::spinOnce();
            loop_rate.sleep();
        }
    }

};


int main(int argc, char **argv){

    ros::init(argc, argv, "talker");

    auto controller = TurtleController();
    controller.run();

    return 0;
}
