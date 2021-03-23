#ifndef COMMON_H
#define COMMON_H

#include <ros/ros.h>
#include <tf/tf.h>
#ifdef INCLUDE_EIGEN
#include <Eigen/Geometry>
#endif
#include <xmlrpcpp/XmlRpc.h>

#define QUA ROS_INFO("\e[33mReached %d\e[0m:%s", __LINE__, __FILE__);
#define QUA_ONCE ROS_INFO_ONCE("\e[33mReached %d\e[0m:%s", __LINE__, __FILE__);

double paramDouble(XmlRpc::XmlRpcValue &param);
std::string paramString (XmlRpc::XmlRpcValue &param);
tf::Pose paramPose (XmlRpc::XmlRpcValue &param);

#ifdef INCLUDE_EIGEN
Eigen::Isometry3d paramPoseEigen(XmlRpc::XmlRpcValue &param);
Eigen::MatrixXd paramMatrix (XmlRpc::XmlRpcValue &param, int rows, int cols);
#endif

class Flag
{
	bool value;
	bool fixed;

public:
	explicit Flag (bool _value = false, bool _fixed = false):
		value(_value),
		fixed(_fixed)
	{}

	bool get () const {
		return value;
	}
	void set (bool _value) {
		value = _value;
	}
	bool isFixed () {
		return fixed;
	}
};

template<typename T>
class ReadyFlags
{
	std::map<T, Flag> flags;
	bool updated;

public:
	explicit ReadyFlags ():
		updated(false)
	{
	}

	void addFlag (T id, bool fixed = false, bool initialValue = false) {
		flags.insert (std::make_pair (id, Flag (initialValue, fixed)));
	}
	void resetFlags () {
		for (typename std::map<T, Flag>::iterator it = flags.begin (); it != flags.end (); it++) {
			if (!it->second.isFixed ())
				it->second.set (false);
		}
	}
	void set (T id) {
		flags[id].set (true);
		updated = true;
	}
	void reset (T id) {
		flags[id].set (false);
		updated = true;
	}
	bool get (T id) const {
		return flags.at (id).get ();
	}
	bool setProcessed () {
		updated = false;
		resetFlags ();
	}
	bool isProcessed () const {
		return !updated;
	}
	bool isReady () const {
		for (typename std::map<T, Flag>::const_iterator it = flags.begin (); it != flags.end (); it++)
			if (!it->second.get ())
				return false;
		return true;
	}
};


#endif // COMMON_H
