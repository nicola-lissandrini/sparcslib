#include "uav_pid_ctrl.h"

#include <Eigen/Geometry>
#include <unsupported/Eigen/EulerAngles>

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

	// Position PID
	ControlParams positionParams(PID_GAINS_NO);

	positionParams["gains"] << _params["position_pid"];
	positionParams.inputSize = D3;
	positionParams.outputSize = D3;
	positionParams.stateSize = 0;
	positionParams.sampleTime = _params.sampleTime;

	positionPid.setParams (positionParams);

	// Angles PID
	ControlParams rpyParams(PID_GAINS_NO);
	rpyParams["gains"] << _params["rpy_pid"];
	rpyParams.inputSize = D3;
	rpyParams.outputSize = D3;
	rpyParams.stateSize = 0;
	rpyParams.sampleTime = _params.sampleTime;

	rpyPid.setParams (rpyParams);
}

#define CONVERT_RANGE(v) (fmod ((v)+M_PI,2*M_PI)-M_PI)

void convertRanges (VectorXd &angles) {
	for (int i = 0; i < angles.size (); i++)
		angles[i] = CONVERT_RANGE(angles[i]);
}

void UavPidControl::updateInput (const VectorXd &state, const VectorXd &ref)
{
	if (!isReady ())
		return;

	// Variables initialization
	Vector3d gravityCompensationWorld = Vector3d::UnitZ () * 9.82 * params["mass"];
	Vector3d statePos = state.head<D3> ();
	Vector4d stateOrient = state.tail<D4> ();
	Quaterniond orientation = Quaterniond (stateOrient[0], stateOrient[1], stateOrient[2], stateOrient[3]);

	// Position PID: position error -> 3D world acceleration
	positionPid.updateInput (statePos, ref);


	Vector3d controlForce = positionPid.getControl () * params["mass"];
	double thrustValue = controlForce[2];

	Vector3d forceCommand = Vector3d::UnitZ () * thrustValue + gravityCompensationWorld;
	//Vector3d stateRpy = EulerAnglesZXYd::FromRotation<false, false, false> (orientation).angles ();
	Vector3d stateRpy = orientation.toRotationMatrix ().eulerAngles (2, 1, 0);
	Vector3d targetRpy;

	convertRanges (stateRpy);

	if (abs (thrustValue) < 0.0001)
		 targetRpy = Vector3d::Zero ();
	else
		targetRpy = params["mass"][0] * 1 / thrustValue * Vector3d(0,1,1).asDiagonal () * targetRpy;

	rpyPid.updateInput (stateRpy, targetRpy);
	Vector3d rpyCommand = rpyPid.getControl ();

	cout << stateRpy << endl << endl;

	// Force - torques -> motor speeds
	Matrix3d inertia = params["inertia"].asDiagonal ();
	Vector3d torqueCommand = inertia * Vector3d (rpyCommand[1], -rpyCommand[2], rpyCommand[0]);

	toScope (0, rpyCommand);

	control = 0 * quadrotor->allocate (forceCommand,  torqueCommand);
}

void UavPidControlNode::stateConvertMsg (VectorXd &_state, const nav_msgs::Odometry &_stateMsg)
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
	ControlParams ctrlParams;

	ctrlParams.inputSize = D3;
	ctrlParams.stateSize = D3 + D4;
	ctrlParams.outputSize = QUAD_PROP_N;
	ctrlParams.sampleTime = 1/paramDouble(params["rate"]);	// TODO: read from parameter server

	ctrlParams.params = {
		{"mass", Eigen::Scalard (paramDouble(params["mass"]))},
		{"position_pid", Eigen::Vector3d (
		 paramDouble(params["position_pid"]["p"]),
		 paramDouble(params["position_pid"]["i"]),
		 paramDouble(params["position_pid"]["d"]))},
		{"rpy_pid", Eigen::Vector3d (
		 paramDouble(params["rpy_pid"]["p"]),
		 paramDouble(params["rpy_pid"]["i"]),
		 paramDouble(params["rpy_pid"]["d"]))},
		{"inertia", Eigen::Vector3d (
		 paramDouble(params["inertia"]["ixx"]),
		 paramDouble(params["inertia"]["iyy"]),
		 paramDouble(params["inertia"]["izz"]))}
	};

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
