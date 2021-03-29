#ifndef UAV_PID_CTRL_H
#define UAV_PID_CTRL_H

#define INCLUDE_EIGEN
#define DEBUG_SCOPE
#ifndef NODE_NAME
# define NODE_NAME "uav_pid_ctrl1"
#endif
#include "../include/sparcsnode.h"
#include "../include/controller_node.h"
#include "uav.h"

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>
#include <mav_msgs/Actuators.h>

#define UAV_GAINS_NO (PID_GAINS_NO + 1 + 2 + 3)

class UavPidControl : public Controller
{
	Pid positionPid;
	Pid rpyPid;
	const Quadrotor *quadrotor;

public:
	UavPidControl (const Quadrotor *_quadrotor);

	void setParams (const ControlParams &_params);
	void updateInput (const Eigen::VectorXd &state, const Eigen::VectorXd &ref);
};


class UavPidControlNode :
		public SparcsControlNode<nav_msgs::Odometry, geometry_msgs::Pose, mav_msgs::Actuators>
{
	Quadrotor quadrotor;
	UavPidControl uavController;

	void initControl ();
	void initUav ();
	void initParams ();

	void stateConvertMsg (Eigen::VectorXd &_state, const nav_msgs::Odometry &_stateMsg);
	void refConvertMsg (Eigen::VectorXd &_ref, const geometry_msgs::Pose &_refMsg);
	void commandConvertMsg (mav_msgs::Actuators &_commandMsg, const Eigen::VectorXd &_command);

public:
	explicit UavPidControlNode ();
};

#endif // UAV_PID_CTRL_H
