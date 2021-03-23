#ifndef PID_H
#define PID_H

#define INCLUDE_EIGEN
#include "common.h"

struct PidParams {
	double ki, kp, kd;
	double sampleTime;
	int stateCount;
};

class Pid
{
	 PidParams params;
	 Eigen::VectorXd integratorState;
	 Eigen::VectorXd lastError;
	 ReadyFlags<std::string> flags;

	 void init ();

public:
	Pid ();

	void setParams (const PidParams &_params);
	PidParams getParams () {
		return params;
	}

	Eigen::VectorXd getControl (const Eigen::VectorXd &refVel, const Eigen::VectorXd &state);
};

#endif // PID_H
