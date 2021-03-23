#include "force_control_node.h"

using namespace ros;
using namespace std;
using namespace XmlRpc;
using namespace Eigen;

ForceControlNode::ForceControlNode():
	SparcsNode(NODE_NAME)
{
	initParams ();
	initROS ();

	flags.addFlag ("odom_received");
	flags.addFlag ("command_received");

	currRef.setZero ();
	integrator.setZero ();
}

void ForceControlNode::initParams ()
{
	PidParams pidParams;

	pidParams.kp = paramDouble (params["pid"]["kp"]);
	pidParams.kd= paramDouble (params["pid"]["kd"]);
	pidParams.ki = paramDouble (params["pid"]["ki"]);
	pidParams.stateCount = STATE_COUNT;
	pidParams.sampleTime = 1 / paramDouble (params["rate"]);

	mass = paramDouble (params["mass"]);
	sync = (bool) params["sync"];

	controller.setParams (pidParams);
}

void ForceControlNode::initROS ()
{
	string odomTopic = paramString (params["odom_topic"]);
	string wrenchTopic = paramString (params["wrench_topic"]);
	string refTopic = paramString (params["ref_topic"]);

	odomSub = nh.subscribe (odomTopic, 1, &ForceControlNode::odometryCallback, this, TransportHints().tcpNoDelay ());
	refSub = nh.subscribe (refTopic, 1, &ForceControlNode::refCallback, this);
	wrenchPub = nh.advertise<geometry_msgs::Wrench> (wrenchTopic, 1);
}

void ForceControlNode::refCallback (const geometry_msgs::Pose &refMsg)
{
	currRef = Vector3d (refMsg.position.x,
						refMsg.position.y,
						refMsg.position.z);

	flags.set ("command_received");
}

void ForceControlNode::odometryCallback(const nav_msgs::Odometry &newOdom)
{
	pos = Vector3d (newOdom.pose.pose.position.x,
					newOdom.pose.pose.position.y,
					newOdom.pose.pose.position.z);
	vel = Vector3d (newOdom.twist.twist.linear.x,
					newOdom.twist.twist.linear.y,
					newOdom.twist.twist.linear.z);;

	flags.set ("odom_received");

	if (!sync)
		step ();
}

#define PID
VectorXd ForceControlNode::controlLaw (const VectorXd &reference)
{
	// Correct ground level
	pos = pos + Vector3d (0, 0, -0.1);
#ifdef PID
	// Get pid output
	Vector3d forceCommand = controller.getControl (reference, pos);
#else
	// Horrible implementation - TODO: make an actual state feedback controller
	PidParams params = controller.getParams ();
	VectorXd state(6);
	VectorXd refExt(6);
	Vector2d singleLqrGain;
	MatrixXd lqrGain(3, 6);
	Vector3d forceCommand;

	state << pos(0), vel(0),
			 pos(1), vel(1),
			 pos(2), vel(2);
	refExt << currRef(0), 0, currRef(1), 0, currRef(2), 0;
	singleLqrGain << params.kp, params.kd;
	lqrGain.block<1, 2> (0, 0) = singleLqrGain;
	lqrGain.block<1, 2> (1, 2) = singleLqrGain;
	lqrGain.block<1, 2> (2, 4) = singleLqrGain;
	VectorXd err = refExt - state;
	VectorXd errOut = currRef - pos;

	integrator += errOut * params.sampleTime;

	forceCommand = lqrGain * err + 0*params.ki * integrator;

#endif
	// Gravity compensation
	Vector3d finalCommand = forceCommand + Vector3d (0, 0, mass * GRAVITY);

	return finalCommand;
}

void ForceControlNode::publishCommand (const VectorXd &command)
{
	geometry_msgs::Wrench wrenchCommand;

	wrenchCommand.force.x = command[0];
	wrenchCommand.force.y = command[1];
	wrenchCommand.force.z = command[2];

	wrenchPub.publish (wrenchCommand);
}

void ForceControlNode::step ()
{
	Vector3d command = controlLaw (currRef);

	publishCommand (command);
}

int ForceControlNode::actions ()
{
	if (!flags.isReady ())
		return 0;

	if (sync)
		step ();

	return 0;
}

int main (int argc, char *argv[])
{
	init (argc, argv, NODE_NAME);
	ForceControlNode fcn;

	return fcn.spin ();
}
