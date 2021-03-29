#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block sparcslib/ROS state IN/Subscribe
extern SimulinkSubscriber<nav_msgs::Odometry, SL_Bus_sparcslib_nav_msgs_Odometry> Sub_sparcslib_1;

// For Block sparcslib/ROS Command out/Publish
extern SimulinkPublisher<geometry_msgs::Wrench, SL_Bus_sparcslib_geometry_msgs_Wrench> Pub_sparcslib_22;

void slros_node_init(int argc, char** argv);

#endif
