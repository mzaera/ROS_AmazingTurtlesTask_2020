#include "ros/ros.h"
#include "std_msgs/String.h"

int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  ros::Publisher name_pub = n.advertise<std_msgs::String>("name_topic", 1000);

  ros::Rate loop_rate(10);

  while (ros::ok())
  {

    std_msgs::String msg;

    msg.data = "MARTI";

    name_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}
