#include "../include/systems.h"

using namespace Eigen;

System::System(Model *_model):
	model(_model)
{
	flags.addFlag ("state_initialized", true);
}

bool System::isDiscrete () {
	return model->params.sampleTime > 0;
}

void LTISystem::updateState (const VectorXd &_input)
{
	assert (_input.size () == linearModel().params.inputSize);

	state = linearModel().stateMatrix * state + linearModel().inputMatrix * _input;

	flags.setProcessed ();
}

VectorXd LTISystem::getOutput (const VectorXd &input) {
	VectorXd outputNoFeedthrough = linearModel().outputMatrix * state;
	if (linearModel().noFeedthrough)
		return outputNoFeedthrough;
	else {
		assert (input.size () == model->params.inputSize);

		return outputNoFeedthrough + linearModel().feedthroughMatrix * input;
	}
}
/*
IntegratorModel::IntegratorModel (int _sampleTime, int _stateSize):
	LinearModel ()
{
	stateMatrix.resize (_stateSize, _stateSize);
	inputMatrix.resize (_stateSize, _stateSize);
	outputMatrix.resize (_stateSize, _stateSize);
	stateMatrix = MatrixXd::Identity (_stateSize, _stateSize);
	inputMatrix = _sampleTime * MatrixXd::Identity (_stateSize, _stateSize);
}

void Integrator::update (const VectorXd &input) {
	updateState (input);
}

VectorXd Integrator::get () {
	return getState ();
}*/

LinearModel::LinearModel(const ModelParams &_params, bool _noFeedthrough):
	Model (_params),
	noFeedthrough(_noFeedthrough)
{
	stateMatrix.resize (params.stateSize, params.stateSize);
	inputMatrix.resize (params.stateSize, params.inputSize);
	outputMatrix.resize (params.outputSize, params.stateSize);

	if (!noFeedthrough)
		feedthroughMatrix.resize (params.inputSize, params.outputSize);
}

DerivatorModel::DerivatorModel (int _inputSize, double _sampleTime):
	LinearModel (ModelParams (2 * _inputSize,
							  _inputSize,
							  _inputSize,
							  _sampleTime),
				 false)
{
	Matrix2d stateBlock;
	Vector2d inputBlock;
	RowVector2d outputBlock;
	double feedthroughBlock;

	stateBlock << 0, 1,
				  0, 0;
	inputBlock << 0, 1;
	outputBlock << -1.0L/params.sampleTime, 0;
	feedthroughBlock = 1.0L/params.sampleTime;

	stateMatrix.setZero ();
	inputMatrix.setZero ();
	outputMatrix.setZero ();
	feedthroughMatrix.setZero ();

	for (int i = 0; i < params.inputSize; i++) {
		stateMatrix.block<2, 2> (2 * i, 2 * i) = stateBlock;
		inputMatrix.block<2, 1> (2 * i, i) = inputBlock;
		outputMatrix.block<1, 2> (i, 2 * i) = outputBlock;
		feedthroughMatrix (i, i) = feedthroughBlock;
	}
}

VectorXd Derivator::step (const VectorXd &input)
{
	updateState (input);

	return getOutput (input);
}

























