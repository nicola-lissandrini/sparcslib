#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "sparcslib";

// For Block sparcslib/ROS state IN/Subscribe
SimulinkSubscriber<nav_msgs::Odometry, SL_Bus_sparcslib_nav_msgs_Odometry> Sub_sparcslib_1;

// For Block sparcslib/ROS Command out/Publish
SimulinkPublisher<geometry_msgs::Wrench, SL_Bus_sparcslib_geometry_msgs_Wrench> Pub_sparcslib_22;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

