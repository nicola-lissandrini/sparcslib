#include "pid.h"

#include <iostream>

using namespace Eigen;
using namespace std;

Pid::Pid ()
{
	flags.addFlag ("params_set");
}

void Pid::setParams (const PidParams &_params)
{
	params = _params;
	flags.set ("params_set");

	init ();
}

void Pid::init ()
{
	integratorState.resize (params.stateCount);
	lastError.resize (params.stateCount);

	integratorState.setZero ();
	lastError.setZero ();
}

VectorXd Pid::getControl (const VectorXd &refVel, const VectorXd &state)
{
	if (!flags.isReady ())
		return VectorXd ();

	VectorXd error = refVel - state;
	VectorXd intError = integratorState;
	VectorXd derivError = (error - lastError) / params.sampleTime;

	integratorState += error * params.sampleTime;
	lastError = error;

	return params.kp * error + params.ki * intError + params.kd * derivError;
}











































