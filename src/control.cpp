#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"


class TurtleController
{
private:
    // The current nodehandle
    ros::NodeHandle n;
   
    // A publisher to publish messages
    ros::Publisher cmd_vel_pub;

    float lin_speed;
    float ang_speed;
    float init_x;
    float init_y;

    // The name of the turtle we are controlling
    std::string turtle_name;

    geometry_msgs::Twist calculateCommand()
    {
        auto msg = geometry_msgs::Twist();
        msg.linear.x = this->lin_speed;
        msg.angular.z = this->ang_speed;
        return msg;
    }

    void spawn_turtle(){

        // Create a service cliente  
        ros::ServiceClient client = n.serviceClient<turtlesim::Spawn>("spawn");

        // call the service
        turtlesim::Spawn srv;
        srv.request.x = this->init_x;
        srv.request.y = this->init_y;
        //srv.request.x = 10.0;
        //srv.request.y = 10.0;
        srv.request.theta = 1;
        srv.request.name = this->turtle_name;
        client.call(srv);
        }

    /*void kill(){

        ros::ServiceClient client = n.serviceClient<turtlesim::kill>("kill");
        turtlesim::kill srv;
        srv.request.name = "turtle1";
        client.call(srv);

    }*/

public:
    TurtleController(){
        // Initialize ROS
        this->n = ros::NodeHandle();

        // Initialize private ROS NodeHandle to change
        // the parameters of the linear and angular speeds
        ros::NodeHandle nh("~");

        // Read private parameters
        nh.param<float>("linear_speed", this->lin_speed, 1.0);
        nh.param<float>("angular_speed", this->ang_speed, 1.0);
        nh.param<std::string>("spawn_turtle_name", this->turtle_name, "");
        nh.param<float>("init_x", this->init_x, 4.0);
        nh.param<float>("init_y", this->init_y, 4.0);

        if (this->turtle_name.length() > 1)
            // Give turtlesim a few seconds to wake up
            ros::Duration(0.2).sleep();
            this->spawn_turtle();

        // Create a publisher object, able to push messages
        this->cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    }

    void run(){
        // Send messages in a loop
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
    // Initialize ROS
    ros::init(argc, argv, "talker");

    // Create our controller object and run it
    auto controller = TurtleController();
    controller.run();

    // And make good on our promise
    return 0;
}
