#include "ros/ros.h"

#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

#include <actionlib/server/simple_action_server.h>
#include "amazing_turtles/MaxvelAction.h"

//--------------------------------------------------Object part-------------------------------------------

class Turtle{
protected:

    ros::NodeHandle nh;

    std::string action_name;
    actionlib::SimpleActionServer<amazing_turtles::MaxvelAction> action_server;
    amazing_turtles::MaxvelFeedback feedback;
    amazing_turtles::MaxvelResult result;

    ros::Publisher cmd_vel_pub;
    geometry_msgs::Twist msg;


public:
    Turtle(std::string name):

        action_server(nh, name, boost::bind(&Turtle::execute, this, _1), false),
        action_name(name)
        {
            init();
            action_server.start();
        } 


    ~Turtle(void)
    {
    }

    void init(){
        cmd_vel_pub =  nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
        msg.linear.x = 0.0;
        msg.angular.z = 0.0;
        cmd_vel_pub.publish(msg);
    }

private:
    void execute(const amazing_turtles::MaxvelGoalConstPtr &goal){

        ros::Rate r(10);
        bool success = true;


        ROS_INFO("ACTION SERVER STARTS");


        for(float i=0.0; i<=goal->max_vel; i+=0.1)
        {
            if (action_server.isPreemptRequested() || !ros::ok())
            {
            ROS_INFO("%s: Preempted", action_name.c_str());
            action_server.setPreempted();
            success = false;
            break;
            }

            msg.linear.x = i;
            msg.angular.z = i;
            cmd_vel_pub.publish(msg);

            feedback.current_vel = i;

            action_server.publishFeedback(feedback);
            r.sleep();
        }

        if(success)
        {
            result.final_vel = feedback.current_vel;
            ROS_INFO("%s: Succeeded", action_name.c_str());
            action_server.setSucceeded(result);
        }
    }

};      



//------------------------------------------Not more in object part--------------------------------------

int main(int argc, char **argv){

    ros::init(argc, argv, "rotation_act");
    ros::NodeHandle n;
    Turtle player("rotation");

    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        //ROS_INFO("Action server working...");
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}