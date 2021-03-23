#ifndef CONTROLLER_H
#define CONTROLLER_H

#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#endif
#include "common.h"
#include "systems.h"
#include <Eigen/Core>

struct ControlParams {
	int inputSize, outputSize, stateSize;
	double sampleTime;
	Eigen::VectorXd gains;

	ControlParams (int _gainsNumber):
		gains(_gainsNumber)
	{}
};

class Controller
{
protected:
	ControlParams params;
	ReadyFlags<std::string> flags;
	Eigen::VectorXd control;

	virtual void init ();

public:
	Controller (int _gainsNumber);

	void setParams (const ControlParams &_params);
	ControlParams getParams ();
	void start () {
		flags.set ("started");
	}

	virtual Eigen::VectorXd getControl () {
		return control;
	}
	virtual void updateInput (const Eigen::VectorXd &state, const Eigen::VectorXd &ref = Eigen::VectorXd ()) = 0;

	bool isReady () {
		return flags.isReady ();
	}
};

#define PID_GAINS_NO 3

class Pid : public Controller
{
	ReadyFlags<std::string> flags;

protected:
	Derivator *derivator;

	virtual void init ();

public:
	Pid ():
		Controller (PID_GAINS_NO)
	{
		flags.addFlag ("setup", true);
	}


	virtual void updateInput  (const Eigen::VectorXd &state, const Eigen::VectorXd &ref);
};


#endif // CONTROLLER_H
