#include "uav_pid_ctrl.h"

#include <Eigen/Geometry>

using namespace ros;
using namespace std;
using namespace XmlRpc;
using namespace Eigen;

UavPidControl::UavPidControl (const Quadrotor *_quadrotor):
	Controller(UAV_GAINS_NO),
	quadrotor(_quadrotor)
{
}

void UavPidControl::setParams (const ControlParams &_params)
{
	Controller::setParams (_params);
	ControlParams pidParams(PID_GAINS_NO);


	pidParams.gains << _params.gains[1], _params.gains[2], _params.gains[3];
	pidParams.inputSize = D3;
	pidParams.outputSize = D3;
	pidParams.stateSize = 0;
	pidParams.sampleTime = _params.sampleTime;

	pidController.setParams (pidParams);
}

void UavPidControl::updateInput (const VectorXd &state, const VectorXd &ref)
{
	if (!isReady ())
		return;

	Vector3d gravityCompensationWorld = Vector3d::UnitZ () * 9.82 * params.gains[0];
	Vector3d gravityCompensationBody;
	Vector3d controlForceWorld, controlForceBody;
	Vector3d statePos = state.head<D3> ();
	Vector4d stateOrient = state.tail<D4> ();
	Quaterniond pose= Quaterniond (stateOrient[0],stateOrient[1], stateOrient[2], stateOrient[3]);
	Matrix3d worldToBody = pose.toRotationMatrix ();
	Vector3d thrust, angularAcceleration;

	pidController.updateInput (statePos, ref);
	controlForceWorld = pidController.getControl ();

	controlForceBody = worldToBody * controlForceWorld;
	gravityCompensationBody = worldToBody * gravityCompensationWorld;

	thrust = Vector3d::UnitZ () * (controlForceBody + gravityCompensationBody).dot (Vector3d::UnitZ ());

	toScope (0, thrust);
	angularAcceleration << params.gains[4] * controlForceWorld[1], params.gains[5] * controlForceWorld[0], 0;


	Matrix3d inertia = Vector3d (params.gains[6], params.gains[7], params.gains[8]).asDiagonal ();

	control = quadrotor->allocate (thrust,  inertia * angularAcceleration);

	toScope (1,Vector3d (0, 0, (worldToBody * (worldToBody.transpose ()) - Matrix3d::Identity ()).norm ()));
}

void UavPidControlNode::stateConvertMsg(VectorXd &_state, const nav_msgs::Odometry &_stateMsg)
{
	_state << _stateMsg.pose.pose.position.x,
			_stateMsg.pose.pose.position.y,
			_stateMsg.pose.pose.position.z,
			_stateMsg.pose.pose.orientation.w,
			_stateMsg.pose.pose.orientation.x,
			_stateMsg.pose.pose.orientation.y,
			_stateMsg.pose.pose.orientation.z;
}

void UavPidControlNode::refConvertMsg(VectorXd &_ref, const geometry_msgs::Pose &_refMsg)
{
	_ref << _refMsg.position.x,
			_refMsg.position.y,
			_refMsg.position.z;
}

void UavPidControlNode::commandConvertMsg(mav_msgs::Actuators &_commandMsg, const VectorXd &_command)
{
	_commandMsg.header.stamp = Time::now ();
	_commandMsg.angular_velocities.resize (_command.size ());

	_commandMsg.angular_velocities[0] = _command[0];
	_commandMsg.angular_velocities[1] = _command[1];
	_commandMsg.angular_velocities[2] = _command[2];
	_commandMsg.angular_velocities[3] = _command[3];
}

UavPidControlNode::UavPidControlNode ():
	SparcsControlNode (NODE_NAME, &uavController),
	uavController(&quadrotor)
{
	initParams ();

	start ();
}

void UavPidControlNode::initControl ()
{
	ControlParams ctrlParams(UAV_GAINS_NO);

	ctrlParams.inputSize = D3;
	ctrlParams.stateSize = D3 + D4;
	ctrlParams.outputSize = QUAD_PROP_N;
	ctrlParams.sampleTime = 1/paramDouble(params["rate"]);	// TODO: read from parameter server

	ctrlParams.gains << paramDouble(params["mass"]),
			paramDouble(params["pid"]["p"]),
			paramDouble(params["pid"]["i"]),
			paramDouble(params["pid"]["d"]),
			paramDouble(params["torque"]["x"]),
			paramDouble(params["torque"]["y"]),
			paramDouble(params["inertia"]["ixx"]),
			paramDouble(params["inertia"]["iyy"]),
			paramDouble(params["inertia"]["izz"]);

	uavController.setParams (ctrlParams);
}

void UavPidControlNode::initUav ()
{
	const double thrustFactor = 8.54858e-06;
	const double dragFactor = thrustFactor * 0.016;
	const double armLength = 0.025 * M_SQRT2;
	const double zOffset = 0.013;

	quadrotor.setPropeller (0, Propeller ("front_right", thrustFactor, dragFactor, CCW_SIGN,
										  Vector3d ( armLength, -armLength, zOffset)));
	quadrotor.setPropeller (1, Propeller ("back_left", thrustFactor, dragFactor, CCW_SIGN,
										  Vector3d (-armLength,  armLength, zOffset)));
	quadrotor.setPropeller (2, Propeller ("front_left", thrustFactor, dragFactor, CW_SIGN,
										  Vector3d ( armLength,  armLength, zOffset)));
	quadrotor.setPropeller (3, Propeller ("back_right", thrustFactor, dragFactor, CW_SIGN,
										  Vector3d (-armLength, -armLength, zOffset)));

	quadrotor.setup ();
}

void  UavPidControlNode::initParams ()
{
	initControl ();
	initUav ();

	addScope ();
	addScope ();
}

int main (int argc, char * argv[])
{
	init (argc, argv, NODE_NAME);
	UavPidControlNode upcn;
	
	return upcn.spin ();
}
