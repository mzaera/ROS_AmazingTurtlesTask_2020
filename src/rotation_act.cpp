#include "ros/ros.h"

#include <actionlib/server/simple_action_server.h>
#include "amazing_turtles/maxvelAction.h"

//--------------------------------------------------Object part-------------------------------------------

class Turtle{
protected:

    ros::NodeHandle nh_;

    std::string action_name_;

    actionlib::SimpleActionServer<amazing_turtles::maxvelAction> action_server_;

    amazing_turtles::maxvelFeedback feedback_;
    amazing_turtles::maxvelResult result_;

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

    void start(){


    }

    void execute(const amazing_turtles::maxvelGoalConstPtr &goal){

    }

};      



//------------------------------------------Not more in object part--------------------------------------

int main(int argc, char **argv){

    ros::init(argc, argv, "rotation_act");

    Turtle player("rotation");

    ros::spin();

    return 0;
}