#include "ros/ros.h"
#include "std_msgs/String.h"


class Listener
{
private:

    ros::NodeHandle n;
	ros::Subscriber sub;

public:
    Listener(){

        this->n = ros::NodeHandle();
        this->sub = n.subscribe("name_topic", 1000, &Listener::printing_Callback, this );

    }

    void run(){

        ros::Rate loop_rate(10);

        while (ros::ok())
        {

            ros::spinOnce();
            loop_rate.sleep();
        }
    }

    void printing_Callback(const std_msgs::String::ConstPtr& msg)
	{
		ROS_INFO("I heard: [%s]", msg->data.c_str());

	}
};


int main(int argc, char **argv){

    ros::init(argc, argv, "v2_normal_Part1");

    auto controller = Listener();
    controller.run();


    return 0;
}

