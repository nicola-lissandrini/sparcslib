#include "controller.h"

using namespace Eigen;

void Controller::init()
{
	control.resize (params.controlSize);
}

Controller::Controller(int _gainsNumber):
	params(_gainsNumber)
{
	flags.addFlag ("params_set", true);
	flags.addFlag ("started", true);
}

void Controller::setParams(const ControlParams &_params)
{
	params = _params;
	flags.set ("params_set");

	init ();
}

ControlParams Controller::getParams() {
	return params;
}

void Pid::init () {
	Controller::init ();

	derivator = new Derivator (params.stateSize, params.sampleTime);
	derivator->initZero ();

	flags.set ("setup");
}

void Pid::updateInput (const Eigen::VectorXd &state, const Eigen::VectorXd &ref)
{
	assert (flags.get ("setup") && "Pid was not set up");

	VectorXd error = ref - state;
	VectorXd derivative = derivator->step (error);

	control = params["gains"][0] * error + params["gains"][2] * derivative;
}
