#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"

#define PI 3.1415926535898




class TurtleController
{
private:
    
    ros::NodeHandle n;

    ros::Publisher cmd_vel_pub;
    //ros::Subscriber sub = n.subscribe("turtle1/pose", 1000, boost::bind(&TurtleController::callBack, this, 1));


public:
    TurtleController(){

        this->n = ros::NodeHandle();
   
        this->cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    }

    void run(){

        ros::Rate loop_rate(10);
        auto msg = geometry_msgs::Twist();

		ros::Time start_time = ros::Time::now();
		ros::Duration transcorregut = ros::Time::now() - start_time;

		ros::Duration periode1(2.0); 
		ros::Duration periode2(3.0); 

        while (ros::ok())
        {
        	transcorregut = ros::Time::now() - start_time;

        	if( transcorregut < periode1){

       			msg.linear.x = 1.0;
        		msg.angular.z = 0.0;
            	this->cmd_vel_pub.publish(msg);

			}else if( transcorregut < periode2) {

       			msg.linear.x = 0.0;
        		msg.angular.z = 2.094395102;
            	this->cmd_vel_pub.publish(msg);

			}else{
				start_time = ros::Time::now();
			}


            ros::spinOnce();
            loop_rate.sleep();

        }
    }

    void callBack(){


    }

};


int main(int argc, char **argv){

    ros::init(argc, argv,"normal2");

    auto controller = TurtleController();
    controller.run();

    return 0;
}
