#ifndef CONTROLLER_H
#define CONTROLLER_H

#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#endif
#include "common.h"
#include "systems.h"
#include <Eigen/Core>
#include <map>

namespace Eigen {
typedef Matrix<double, 1, 1> Scalard;
}

#define CTR_ASYNC (-1)

struct ControlParams {

	int controlSize, stateSize, refSize;
	double sampleTime;
	std::map<std::string, Eigen::VectorXd> params;

	ControlParams (int _gainsNumber):
		params({{"gains", Eigen::VectorXd (_gainsNumber)}})
	{}

	ControlParams () {}

	Eigen::VectorXd &operator[] (const std::string &_name) {
		return params[_name];
	}

	Eigen::VectorXd operator[] (const std::string &_name) const {
		return params.at (_name);
	}
};

std::ostream &operator<<(std::ostream &os, const ControlParams &dt) {
	os << "outputSize: " << dt.controlSize <<
		  "\nstateSize: " << dt.stateSize <<
		  "\nrefSize: " << dt.refSize <<
		  "\nparams: ";
	for (auto& t : dt.params)
		os << "{" << t.first << ": " << t.second << "}\n";

	return os;
}

class Controller
{
protected:
	ControlParams params;
	ReadyFlags<std::string> flags;
	Eigen::VectorXd control;

	virtual void init ();

public:
	Controller (int _gainsNumber = 0);

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
