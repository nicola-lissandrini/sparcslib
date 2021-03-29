#include "../include/sparcsnode.h"

#include <Eigen/Geometry>


using namespace ros;
using namespace std;
using namespace tf;
using namespace XmlRpc;

const char *xmlRpcErrorStrings[] = {
	"TypeInvalid",
	"TypeBoolean",
	"TypeInt",
	"TypeDouble",
	"TypeString",
	"TypeDateTime",
	"TypeBase64",
	"TypeArray",
	"TypeStruct"
};

void paramError (XmlRpcValue::Type actual, XmlRpcValue::Type expected, string name) {
	stringstream msg;

	msg << "Invalid datatype in tag '" << (name == ""?"unknown": name) << "'. Expecting " << xmlRpcErrorStrings[(int) expected] << ", got " << xmlRpcErrorStrings[(int) actual];
	ROS_ERROR_STREAM (msg.str());
	throw XmlRpcException (msg.str ());
}

double paramDouble (XmlRpcValue &params, string name, const boost::optional<double> &defaultValue) {
	return paramDouble (params[name], -1, name, defaultValue);
}

double paramDouble (XmlRpcValue &param, int index, string parentName, const boost::optional<double> &defaultValue)
{
	XmlRpcValue curr = (index >= 0? param[index] : param);
	switch (curr.getType ()) {
	case XmlRpcValue::TypeInt:
		return (double) int (curr);
	case XmlRpcValue::TypeDouble:
		return double (curr);
	case XmlRpcValue::TypeInvalid:
		if (defaultValue)
			return defaultValue.value ();
	default:
		paramError (curr.getType (), XmlRpcValue::TypeDouble, parentName);
	}
}

int paramInt (XmlRpcValue &params, string name)
{
	XmlRpcValue param = params[name];

	if (param.getType () == XmlRpcValue::TypeInt)
		return int (param);
	else
		paramError (param.getType (), XmlRpcValue::TypeInt, name);
}

bool paramBool (XmlRpcValue &params, string name)
{
	XmlRpcValue param = params[name];

	if (param.getType () == XmlRpcValue::TypeBoolean)
		return bool (param);
	else
		paramError (param.getType (), XmlRpcValue::TypeBoolean, name);
}

string paramString (XmlRpcValue &params, string name)
{
	XmlRpcValue param = params[name];

	if (param.getType () != XmlRpcValue::TypeString)
		paramError (param.getType (), XmlRpcValue::TypeString, name);
	else
		return string (param);
}

Pose paramPose (XmlRpcValue &params, string name)
{
	XmlRpcValue param = params[name];

	Pose ret;

	ret.setOrigin (Vector3 (
					paramDouble (param["pos"],"x"),
					paramDouble (param["pos"],"y"),
					paramDouble (param["pos"],"z")));
	ret.setRotation (Quaternion (
					paramDouble (param["rot"],"x"),
					paramDouble (param["rot"],"y"),
					paramDouble (param["rot"],"z"),
					paramDouble (param["rot"],"w")));
	return ret;
}
Range paramRange (XmlRpcValue &params, string name)
{
	XmlRpcValue param = params[name];
	Range ret;

	ret.min = paramDouble (param, "min");
	ret.max = paramDouble (param, "max");

	ret.step = paramDouble (param, "step", NAN);

	return ret;
}

Eigen::Isometry3d paramPoseEigen (XmlRpcValue &params, string name)
{
	XmlRpcValue param = params[name];

	Eigen::Translation3d tr(
					paramDouble (param["pos"],"x"),
					paramDouble (param["pos"],"y"),
					paramDouble (param["pos"],"z"));
	Eigen::Quaterniond rot =  Eigen::Quaterniond (
					paramDouble (param["rot"],"w"),
					paramDouble (param["rot"],"x"),
					paramDouble (param["rot"],"y"),
					paramDouble (param["rot"],"z"));
	return tr * rot;
}

// Row major
Eigen::MatrixXd paramMatrix (XmlRpcValue &params, string name, int rows, int cols)
{
	XmlRpcValue param = params[name];
	Eigen::MatrixXd ret;

	ret.resize (rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			ret(i,j) = paramDouble (param,i*cols + j, name);
	}

	return ret;
}

Eigen::VectorXd paramVector (XmlRpcValue &params, string name)
{
	XmlRpcValue param = params[name];
	if (param.getType () != XmlRpcValue::TypeArray)
		paramError (param.getType (), XmlRpcValue::TypeArray, name);

	const int size = param.size ();
	Eigen::VectorXd ret(size);

	for (int i = 0; i < size; i++)
		ret[i] = paramDouble (param, i, name);

	return ret;
}


std::ostream &operator << (std::ostream &os, const Range &range) {
	os << "[" << range.min << ":" << range.step << ":" << range.max << "] (size " << range.count () << ")";
	return os;
}

SparcsNode::SparcsNode (string _name):
	name(_name)
{
	initParams ();
	initROS ();
}

void SparcsNode::initParams ()
{
	try {
		nh.getParam (name, params);
	} catch (const XmlRpcException &e) {
		ROS_ERROR ("Error loading params: %s",e.getMessage ().c_str ());
	}
}

void SparcsNode::initROS ()
{
	rate = new Rate (paramDouble (params, "rate"));
}

int SparcsNode::spin ()
{
	int ret;

	while (ok ()) {
		ret = actions ();

		if (ret)
			return ret;

		spinOnce ();
		rate->sleep ();
	}

	return 0;
}






































