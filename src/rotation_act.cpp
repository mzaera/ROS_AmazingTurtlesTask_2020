#include "ros/ros.h"

#include <actionlib/server/simple_action_server.h>
#include "amazing_turtles/MaxvelAction.h"

//--------------------------------------------------Object part-------------------------------------------

class Turtle{
protected:

    ros::NodeHandle nh_;

    std::string action_name_;

    actionlib::SimpleActionServer<amazing_turtles::MaxvelAction> action_server_;

    amazing_turtles::MaxvelFeedback feedback_;
    amazing_turtles::MaxvelResult result_;

public:
    Turtle(std::string name):

        action_server_(nh_, name, boost::bind(&Turtle::execute, this, _1), false),
        action_name_(name)
        {
            action_server_.start();
        } 


    ~Turtle(void)
    {
    }

    void execute(const amazing_turtles::MaxvelGoalConstPtr &goal){

        ros::Rate r(1);
        bool success = true;


        ROS_INFO("HI MARTI");


        for(int i=1; i<=goal->order; i++)
        {
            if (action_server_.isPreemptRequested() || !ros::ok())
            {
            ROS_INFO("%s: Preempted", action_name_.c_str());
            action_server_.setPreempted();
            success = false;
            break;
            }

        feedback_.sequence = i;

        action_server_.publishFeedback(feedback_);
        r.sleep();
        }

        if(success)
        {
            result_.sequence = feedback_.sequence;
            ROS_INFO("%s: Succeeded", action_name_.c_str());
            action_server_.setSucceeded(result_);
        }
    }

};      



//------------------------------------------Not more in object part--------------------------------------

int main(int argc, char **argv){

    ros::init(argc, argv, "rotation_act");
    ros::NodeHandle n;
    Turtle player("rotation");

    ros::Rate loop_rate(0.5);
    while (ros::ok())
    {
        ROS_INFO("Action server working");
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}