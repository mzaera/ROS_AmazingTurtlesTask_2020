#include <iostream>
#include <stdlib.h>  

#include "ros/ros.h"

#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

#include "turtlesim/Pose.h"
#include "turtlesim/Spawn.h"
#include "turtlesim/TeleportAbsolute.h"
#include "turtlesim/Kill.h"

#include <actionlib/server/simple_action_server.h>
#include "amazing_turtles/RaceAction.h"

//--------------------------------------------------Spawn & Kill-------------------------------------------


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

//--------------------------------------------------Object Turtle-------------------------------------------

class Turtle{
protected:

    ros::NodeHandle nh_2;
    ros::Publisher cmd_vel;
    ros::Subscriber sub;

    std::string name;
    turtlesim::Pose actual_pose;
    geometry_msgs::Twist msg;

    ros::Time start_time;

    bool info;


public:
    Turtle(std::string turtle_name, std::string sub_topic, std::string pub_topic){
    
        name = turtle_name;
        sub = nh_2.subscribe(sub_topic, 1000, &Turtle::pose_Callback, this );
        cmd_vel =  nh_2.advertise<geometry_msgs::Twist>(pub_topic, 1000);

    }

    ~Turtle(void)
    {
    }

    void pose_Callback(const turtlesim::PoseConstPtr& pose){
        actual_pose.x = pose->x;
    }

    void run(float final){

        msg.linear.x = RandomFloat( 0.1, 1.0 );
        cmd_vel.publish(msg);

    }

    float act_pos(){
        return actual_pose.x;
    }


    float RandomFloat(float a, float b) {
        float random = ((float) rand()) / (float) RAND_MAX;
        float diff = b - a;
        float r = random * diff;
        return a + r;
    }

};

//--------------------------------------------------Object Action-------------------------------------------


class Action{
protected:

    ros::NodeHandle nh;

    std::string action_name;
    actionlib::SimpleActionServer<amazing_turtles::RaceAction> action_server;

    amazing_turtles::RaceFeedback feedback;
    amazing_turtles::RaceResult result;




public:
    Action(std::string name):

        action_server(nh, name, boost::bind(&Action::execute, this, _1), false),
        action_name(name)
        {
            action_server.start();
        } 


    ~Action(void)
    {
    }



    void execute(const amazing_turtles::RaceGoalConstPtr &goal){

        ros::Rate r(100);
        bool success = true;
        bool race = true;

        ROS_INFO("ACTION SERVER STARTS");

        float act_pos1, act_pos2, act_pos3, act_pos4;

        Turtle player1("Amazing_Turtle_1","player1/pose", "player1/cmd_vel");
        Turtle player2("Amazing_Turtle_2","player2/pose", "player2/cmd_vel");
        Turtle player3("Amazing_Turtle_3","player3/pose", "player3/cmd_vel");
        Turtle player4("Amazing_Turtle_4","player4/pose", "player4/cmd_vel");

        kill("turtle1");
        spawn(1.0,8.54,"player1");
        spawn(1.0,6.54,"player2");
        spawn(1.0,4.54,"player3");
        spawn(1.0,2.54,"player4");

        ros::Duration(0.2).sleep();

        while(race) 
        {
            if (action_server.isPreemptRequested() || !ros::ok())
            {
                ROS_INFO("%s: Preempted", action_name.c_str());
                action_server.setPreempted();
                success = false;
                break;
            }

            player1.run(goal->final_pos);
            player2.run(goal->final_pos);
            player3.run(goal->final_pos);
            player4.run(goal->final_pos);

            act_pos1 = player1.act_pos();
            act_pos2 = player2.act_pos();
            act_pos3 = player3.act_pos();
            act_pos4 = player4.act_pos();

            feedback.current_winner = actual_winner(act_pos1, act_pos2, act_pos3, act_pos4);
            action_server.publishFeedback(feedback);

            race = continue_race(act_pos1, act_pos2, act_pos3, act_pos4,goal->final_pos);

        }

        if(success)
        {
            result.final_winner = feedback.current_winner;
            ROS_INFO("%s: Succeeded", action_name.c_str());
            action_server.setSucceeded(result);
        }
        ros::Duration(10.0).sleep();
        kill("player1");
        kill("player2");
        kill("player3");
        kill("player4");
        spawn(5.544445,5.544445,"turtle1");

    }

    std::string actual_winner(float act_pos1, float act_pos2, float act_pos3, float act_pos4){

        int max = act_pos1;
        std::string to_return = "Amazing_Turtle_1";

        if(act_pos2 > max ){ max=act_pos2; to_return = "Amazing_Turtle_2"; }
        if(act_pos3 > max ){ max=act_pos3; to_return = "Amazing_Turtle_3"; }
        if(act_pos4 > max ){ max=act_pos4; to_return = "Amazing_Turtle_4"; }

        return  to_return;
    }

    bool continue_race(float act_pos1, float act_pos2, float act_pos3, float act_pos4,float end){

        bool to_return = true;

        if(act_pos1 > end ){  to_return = false; }
        if(act_pos2 > end ){  to_return = false; }
        if(act_pos3 > end ){  to_return = false; }
        if(act_pos4 > end ){  to_return = false; }

        return  to_return;
    }
};     



//------------------------------------------Not more in object part--------------------------------------

int main(int argc, char **argv){

    ros::init(argc, argv, "action_race");
    Action race("race");
    
    ros::spin();

    return 0;
}