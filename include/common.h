#ifndef COMMON_H
#define COMMON_H

#include <ros/ros.h>
#include <tf/tf.h>
#include <chrono>
#ifdef INCLUDE_EIGEN
#include <Eigen/Geometry>
#endif
#include <xmlrpcpp/XmlRpc.h>


#ifdef _GAZEBO_CONSOLE_HH_
#define GZQUA gzmsg << std::string(__FILE__) << ":" << __LINE__ << " Reached" << endl;
#endif

// [0,2pi) to [-pi, pi)
#define CONVERT_RANGE(v) (fmod ((v)+M_PI,2*M_PI)-M_PI)

#define QUA ROS_INFO("\e[33mReached %s\e[0m:%d", __PRETTY_FUNCTION__, __LINE__);
#define QUA_ONCE ROS_INFO_ONCE("\e[33mReached %s\e[0m:%d", __PRETTY_FUNCTION__, __LINE__);

// To be used in class definitions
#define DEF_SHARED(classname) using Ptr = std::shared_ptr<classname>;

struct Range {
	double min, max, step;

	int count () const {
		if (step != NAN)
			return (int) floor ((max - min)/step);
		else
			return -1;
	}

	double width () const {
		return max - min;
	}
};

std::ostream &operator << (std::ostream &os, const Range &range);
// ROS params

void paramError (XmlRpc::XmlRpcValue::Type actual, XmlRpc::XmlRpcValue::Type expected, std::string name = "");
double paramDouble(XmlRpc::XmlRpcValue &params, std::string name, const boost::optional<double> &defaultValue = boost::none);
double paramDouble(XmlRpc::XmlRpcValue &param, int index, std::string parentName, const boost::optional<double> &defaultValue = boost::none);
int paramInt (XmlRpc::XmlRpcValue &params, std::string name);
bool paramBool (XmlRpc::XmlRpcValue &params, std::string name);
std::string paramString (XmlRpc::XmlRpcValue &params, std::string name);
tf::Pose paramPose (XmlRpc::XmlRpcValue &params);
Range paramRange (XmlRpc::XmlRpcValue &params, std::string name);
template<typename T>
T paramEnum (XmlRpc::XmlRpcValue &params, std::string name, std::vector<std::string> values)
{
	std::string value = paramString (params, name);
	auto selected = std::find (values.begin (), values.end (), value);

	if (selected == values.end ()) {
		std::stringstream msg;
		msg << "Invalid enum value '" << value << "' in tag '" << name << "'";
		ROS_ERROR_STREAM (msg.str());
		throw XmlRpc::XmlRpcException (msg.str());
	} else
		return (T) std::distance (values.begin (), selected);
}

#ifdef INCLUDE_EIGEN
Eigen::Isometry3d paramPoseEigen(XmlRpc::XmlRpcValue &params, std::string name);
Eigen::MatrixXd paramMatrix (XmlRpc::XmlRpcValue &params, std::string name, int rows, int cols);
Eigen::VectorXd paramVector (XmlRpc::XmlRpcValue &params, std::string name);
#endif

// Profiling
template<typename F>
double profile (const F &lambda, int ndiv = 1) {
	double taken;
	auto _start = std::chrono::steady_clock::now ();
	lambda();
	auto _end = std::chrono::steady_clock::now ();
	taken = double(std::chrono::duration_cast<std::chrono::microseconds> (_end - _start).count ())/1e3;
#ifndef DISABLE_PROFILE_OUTPUT
	if (ndiv == 1)
		std::cout << "Taken: " << taken << std::endl;
	else
		std::cout << "Total: " << taken << "ms each: " << taken/double(ndiv) << "ms over " << ndiv << " trials" << std::endl;
#endif
	return taken;
}

#define PROFILE_N_EN(taken, lambda, ndiv, enable) {\
	std::stringstream ID;\
	ID << __PRETTY_FUNCTION__ << ":" << __LINE__-2;\
	auto _start = std::chrono::steady_clock::now ();\
	lambda();\
	auto _end = std::chrono::steady_clock::now ();\
	taken = double(std::chrono::duration_cast<std::chrono::microseconds> (_end - _start).count ())/1e3;\
	if (enable) {\
	if (ndiv == 1) std::cout << ID.str() << ": taken: " << taken << "ms" << std::endl;\
	else std::cout << ID.str() << ": total: " << taken << "ms each: " << taken/double(ndiv) << "ms over " << ndiv << " trials" << std::endl; }}

#ifdef DISABLE_PROFILE_OUTPUT
#define PROFILE_N(taken,lambda,ndiv) PROFILE_N_EN(taken,lambda,ndiv,false)
#else
#define PROFILE_N(taken,lambda,ndiv) PROFILE_N_EN(taken,lambda,ndiv,true)
#endif
#define PROFILE(taken, lambda) PROFILE_N(taken,lambda,1)


// Dimensions
#define D_2D 2
#define D_3D 3
#define D_4D 4

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
	bool operator[] (T id) const {
		return get (id);
	}
	void setProcessed () {
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
