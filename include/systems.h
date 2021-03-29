#ifndef SYSTEMS_H
#define SYSTEMS_H

#define INCLUDE_EIGEN
#include "../include/common.h"
#include <Eigen/Core>

struct ModelParams
{
	int stateSize;
	int inputSize;
	int outputSize;
	double sampleTime;

	ModelParams (int _stateSize, int _inputSize, int _outputSize, double _sampleTime):
		stateSize(_stateSize),
		inputSize(_inputSize),
		outputSize(_outputSize),
		sampleTime(_sampleTime)
	{}
};

struct Model
{
	ModelParams params;

	Model (const ModelParams &_params):
		params(_params)
	{
	}
};

class System
{
protected:
	Model *model;
	Eigen::VectorXd state;
	ReadyFlags<std::string> flags;

public:
	System (Model *_model);

	void initState (const Eigen::VectorXd &_state) {
		state = _state;
		flags.set ("state_initialized");
	}

	void initZero () {
		initState (Eigen::VectorXd::Zero (model->params.stateSize));
	}

	Eigen::VectorXd getState () {
		return state;
	}

	virtual void updateState (const Eigen::VectorXd &input = Eigen::VectorXd ()) = 0;

	void setModel (const Model *_model);
	bool isDiscrete ();
};


struct LinearModel : public Model
{
	Eigen::MatrixXd stateMatrix;
	Eigen::MatrixXd inputMatrix;
	Eigen::MatrixXd outputMatrix;
	Eigen::MatrixXd feedthroughMatrix;

	bool noFeedthrough;

	LinearModel (const ModelParams &_params, bool _noFeedthrough = true);

	LinearModel (const LinearModel &_copy):
		Model(_copy.params)
	{
	}
};

class LTISystem : public System
{
public:
	LTISystem (LinearModel *_model):
		System (_model)
	{
		if (model->params.sampleTime > 0)
			flags.set ("model_set");
	}

	const LinearModel &linearModel () const {
		return reinterpret_cast<const LinearModel &> (*model);
	}
	virtual void updateState (const Eigen::VectorXd &_input);
	Eigen::VectorXd getOutput (const Eigen::VectorXd &input);
};


class DerivatorModel : public LinearModel
{
public:
	DerivatorModel (int _inputSize, double _sampleTime);
};

// TODO generalize derivative estimation
class Derivator : private LTISystem
{
public:
	Derivator (int _inputSize, double _sampleTime):
		LTISystem (new DerivatorModel (_inputSize, _sampleTime))
	{
	}

	void initState (const Eigen::VectorXd &_initialState) {
		initZero ();

		updateState (_initialState);
	}

	void initZero () {
		System::initZero ();
	}

	Eigen::VectorXd step (const Eigen::VectorXd &input);
};




#endif // SYSTEMS_H













