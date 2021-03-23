#include "../include/sparcsnode.h"
#include <Eigen/Geometry>

using namespace ros;
using namespace std;
using namespace tf;
using namespace XmlRpc;

double paramDouble (XmlRpcValue &param)
{
	switch (param.getType ())
	{
	case XmlRpcValue::TypeInt:
		return (double) int (param);
	case XmlRpcValue::TypeDouble:
		return double (param);
	default:
		ROS_ERROR ("Invaild datatype %d, expecting %d",param.getType (), XmlRpcValue::TypeDouble);
		throw XmlRpcException ("Invalid datatype, expecting double");
	}
}

string paramString (XmlRpcValue &param)
{
	if (param.getType () != XmlRpcValue::TypeString)
		throw XmlRpcException ("Invalid datatype, expecting string");
	return string (param);
}

Pose paramPose (XmlRpcValue &param)
{
	Pose ret;

	ret.setOrigin (Vector3 (
					paramDouble (param["pos"]["x"]),
					paramDouble (param["pos"]["y"]),
					paramDouble (param["pos"]["z"])));
	ret.setRotation (Quaternion (
					paramDouble (param["rot"]["x"]),
					paramDouble (param["rot"]["y"]),
					paramDouble (param["rot"]["z"]),
					paramDouble (param["rot"]["w"])));
	return ret;
}

Eigen::Isometry3d paramPoseEigen (XmlRpcValue &param)
{
	Eigen::Translation3d tr(
					paramDouble (param["pos"]["x"]),
					paramDouble (param["pos"]["y"]),
					paramDouble (param["pos"]["z"]));
	Eigen::Quaterniond rot =  Eigen::Quaterniond (
					paramDouble (param["rot"]["w"]),
					paramDouble (param["rot"]["x"]),
					paramDouble (param["rot"]["y"]),
					paramDouble (param["rot"]["z"]));
	return tr * rot;
}

// Row major
Eigen::MatrixXd paramMatrix (XmlRpcValue &param, int rows, int cols)
{
	Eigen::MatrixXd ret;

	ret.resize (rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			ret(i,j) = paramDouble (param[i*cols + j]);
	}

	return ret;
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
	rate = new Rate (paramDouble (params["rate"]));
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






































