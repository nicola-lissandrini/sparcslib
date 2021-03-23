#ifndef CONTROLLER_NODE_H
#define CONTROLLER_NODE_H

#include "controller.h"
#include "sparcsnode.h"

template<class StateT, class RefT, class CommandT, bool sync = false>
class SparcsControlNode : public SparcsNode
{
	Controller *controller;
	StateT stateMsg;
	RefT refMsg;
	CommandT commandMsg;

	void stateCallback ( StateT newStateMsg) {
		stateMsg = newStateMsg;

		if (sync)
			controlStep ();
	}

	void refCallback (const RefT &newRefMsg) {
		refMsg = newRefMsg;
	}

	// Compute command msg
	int controlStep () {
		ControlParams controlParams = controller->getParams ();
		Eigen::VectorXd command;
		Eigen::VectorXd state(controlParams.stateSize);
		Eigen::VectorXd ref(controlParams.inputSize);

		stateConvertMsg (state, stateMsg);
		refConvertMsg (ref, refMsg);

		controller->updateInput (state, ref);

		command = controller->getControl ();


		commandConvertMsg (commandMsg, command);

		return 0;
	}

protected:
	void start () {
		controller->start ();
	}

	int actions () {
		if (!controller->isReady ())
			return 0;

		if (!sync) {
			// Get command
			int ret = controlStep ();

			// Error occured
			if (ret)
				return ret;

			// Publish command if no error
			publish ("command", commandMsg);
		}

		return 0;
	}

protected:
	virtual void stateConvertMsg (Eigen::VectorXd &_state, const StateT &_stateMsg) = 0;
	virtual void refConvertMsg (Eigen::VectorXd &_ref, const RefT &_refMsg) = 0;
	virtual void commandConvertMsg (CommandT &_commandMsg, const Eigen::VectorXd &_command) = 0;

	virtual void initROS () {
		std::string stateTopic = paramString (params["state_topic"]);
		std::string refTopic = paramString (params["ref_topic"]);
		std::string commandTopic = paramString (params["command_topic"]);

		addSub ("state", stateTopic, 1, &SparcsControlNode::stateCallback);
		addSub ("ref", refTopic, 1, &SparcsControlNode::refCallback);
		addPub<CommandT> ("command", commandTopic, 1);
	}

public:
	SparcsControlNode (std::string _name, Controller *_controller):
		SparcsNode(_name),
		controller(_controller)
	{
		initROS ();
	}

};

#endif // CONTROLLER_NODE_H
