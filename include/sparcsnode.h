#ifndef PD_ROSNODE_H
#define PD_ROSNODE_H

#include "common.h"
#include <std_msgs/Float64MultiArray.h>

#define NODE_INFO(...) ROS_INFO("\e[38;5;82m\e[1m"  NODE_NAME ":\e[0m " __VA_ARGS__)
#define NODE_ERROR(...) ROS_ERROR("\e[38;5;82m\e[1m"  NODE_NAME  ":\e[0m " __VA_ARGS__)

typedef std::map<std::string, ros::Publisher> NamedPubList;
typedef std::map<std::string, ros::Subscriber> NamedSubList;

template<class T, class M>
void addSub (
		NamedSubList &subList,
		ros::NodeHandle &nh,
		const std::string &name,
		const std::string &topic,
		uint32_t queueSize,
		void (M::*fp)(T),
		M *obj,
		const ros::TransportHints &transportHints = ros::TransportHints ())
{
	subList.insert (std::make_pair (name, nh.subscribe(topic, queueSize, fp, obj, transportHints)));
}

template<class T>
void addPub (
		NamedPubList &pubList,
		ros::NodeHandle &nh,
		const std::string &name,
		const std::string &topic,
		uint32_t queueSize,
		bool latch = false)
{
	pubList.insert (std::make_pair (name, nh.advertise<T> (topic, queueSize, latch)));
}

// Define publishers available everywhere in the code
// Warning: not reentrant, intended for debug only
#ifdef DEBUG_SCOPE

# ifndef INCLUDE_EIGEN
#  error To use debug scopes you must enable Eigen inclusion by defining INCLUDE_EIGEN before including sparcsnode.h
# endif // INCLUDE_EIGEN

#define SCOPE_DEF_NAME "sl_scope_"

NamedPubList scopes;
int scopeCount(0);

void addScope (const std::string &name = "")
{
	ros::NodeHandle newNodeHandle;
	std::string topicName = name.length () ? name : SCOPE_DEF_NAME + std::to_string (scopeCount);
	scopeCount++;

	addPub<std_msgs::Float64MultiArray> (scopes, newNodeHandle, topicName, topicName, 1);
}

void toScope (const std::string &name, const Eigen::VectorXd &signal)
{
	std_msgs::Float64MultiArray signalMsg;

	signalMsg.layout.dim.resize (1);
	signalMsg.layout.dim[0].label = name;
	signalMsg.layout.dim[0].size = signal.size ();
	signalMsg.layout.dim[0].stride = signal.size ();
	signalMsg.data.resize (signal.size ());
	Eigen::VectorXd::Map (signalMsg.data.data (), signal.size ()) = signal;

	scopes[name].publish (signalMsg);
}

void toScope (int id, const Eigen::VectorXd &signal) {
	assert (id < scopeCount && "Scope id not existing");
	toScope (SCOPE_DEF_NAME + std::to_string (id), signal);
}

#endif // DEBUG_SCOPE

class SparcsNode
{
	std::string name;
	NamedPubList publishers;
	NamedSubList subscribers;

protected:
	ros::NodeHandle nh;
	ros::Rate *rate;
	XmlRpc::XmlRpcValue params;

	template<class T, class M>
	void addSub (const std::string &name,
				 const std::string &topic,
				 uint32_t queueSize,
				 void (M::*fp)(T),
				 const ros::TransportHints &transportHints = ros::TransportHints ())
	{
		::addSub<T, M> (subscribers, nh, name, topic, queueSize, fp,reinterpret_cast<M *> (this), transportHints);
	}

	template<class T>
	void addPub (const std::string &name,
				 const std::string &topic,
				 uint32_t queueSize,
				 bool latch = false)
	{
		::addPub<T> (publishers, nh, name, topic, queueSize, latch);
	}

	template<class T>
	void publish (const std::string &name, const T &msg) {
		publishers[name].publish (msg);
	}

	virtual void initParams ();
	virtual void initROS ();

	virtual int actions () = 0;

public:
	SparcsNode (std::string _name);

	int spin ();
	std::string getName () {
		return name;
	}
};


#endif // PD_ROSNODE_H

























