#ifndef FORCECONTROL_NODE_H
#define FORCECONTROL_NODE_H

#define INCLUDE_EIGEN
#ifndef NODE_NAME
# define NODE_NAME "force_control_node"
#endif
#include "sparcsnode.h"

#include "pid.h"

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Wrench.h>
#include <tf_conversions/tf_eigen.h>

#define STATE_COUNT 3
#define GRAVITY 9.8

class ForceControlNode : public SparcsNode
{
	Pid controller;
	double mass;
	bool sync;
	ReadyFlags<std::string> flags;

	ros::Subscriber odomSub;
	ros::Subscriber refSub;
	ros::Publisher wrenchPub;
	Eigen::Vector3d pos, vel, currRef;
	Eigen::Vector3d integrator;


	void initParams ();
	void initROS ();
	int actions ();

	void odometryCallback (const nav_msgs::Odometry &newOdom);
	void refCallback (const geometry_msgs::Pose &refMsg);
	Eigen::VectorXd controlLaw (const Eigen::VectorXd &reference);
	void publishCommand (const Eigen::VectorXd &command);
	void step ();

public:
	ForceControlNode ();
};

#endif // FORCECONTROL_NODE_H
