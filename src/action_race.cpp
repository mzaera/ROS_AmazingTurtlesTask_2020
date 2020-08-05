#include "ros/ros.h"

#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

#include <actionlib/server/simple_action_server.h>
#include "amazing_turtles/RaceAction.h"

//--------------------------------------------------Object part-------------------------------------------

class Action{
protected:

    ros::NodeHandle nh;

    std::string action_name;
    actionlib::SimpleActionServer<amazing_turtles::RaceAction> action_server;

    amazing_turtles::RaceFeedback feedback;
    amazing_turtles::RaceResult result;

    ros::Publisher cmd_vel_pub;
    geometry_msgs::Twist msg;


public:
    Action(std::string name):

        action_server(nh, name, boost::bind(&Action::execute, this, _1), false),
        action_name(name)
        {
            init();
            action_server.start();
        } 


    ~Action(void)
    {
    }

    void init(){
        cmd_vel_pub =  nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
        msg.linear.x = 0.0;
        msg.angular.z = 0.0;
        cmd_vel_pub.publish(msg);
    }

private:
    void execute(const amazing_turtles::RaceGoalConstPtr &goal){

        ros::Rate r(10);
        bool success = true;
        ROS_INFO("ACTION SERVER STARTS");


        while(true) //condicio que jo vulgui
        {
            if (action_server.isPreemptRequested() || !ros::ok())
            {
                ROS_INFO("%s: Preempted", action_name.c_str());
                action_server.setPreempted();
                success = false;
                break;
            }

 



        }

        if(success)
        {
            ROS_INFO("%s: Succeeded", action_name.c_str());
            action_server.setSucceeded(result);
        }

    }

};      



//------------------------------------------Not more in object part--------------------------------------

int main(int argc, char **argv){

    ros::init(argc, argv, "action_race");
    ros::NodeHandle n;
    //Action player("rotation");

    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        //ROS_INFO("Action server working...");
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}