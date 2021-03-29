#ifndef UAV_H
#define UAV_H

#define INCLUDE_EIGEN
#include "../include/common.h"
#include <Eigen/Core>

struct Propeller
{
	std::string name;
	Eigen::Isometry3d pose;

	// Proportionality between ang vel and thrust force
	double thrustFactor;
	// Proportionality between ang vel and drag torque
	double dragFactor;
	// Can be either +1 or -1
	double dragSign;

	Propeller (std::string _name,
			   double _thrustFactor,
			   double _dragFactor,
			   double _dragSign,
			   Eigen::Isometry3d _pose);

	Propeller (std::string _name,
			   double _thrustFactor,
			   double _dragFactor,
			   double _dragSign,
			   Eigen::Vector3d _position,
			   Eigen::Quaterniond _orientation);


	Propeller (std::string _name,
			   double _thrustFactor,
			   double _dragFactor,
			   double _dragSign,
			   Eigen::Vector3d _position,
			   double _roll = 0,
			   double _pitch = 0,
			   double _yaw = 0);

	Propeller () {}

	// Propeller (const XmlRpc::XmlRpcValue &param);
};

#define CW_SIGN (-1.0L)
#define CCW_SIGN (1.0L)

typedef Eigen::Matrix<double, 2 * D3, Eigen::Dynamic> AllocationMatrix;


class Uav
{
	ReadyFlags<std::string> flags;
	std::string name;
	std::vector<Propeller> propellers;
	int rotorsNumber;

protected:

	AllocationMatrix allocationMatrix;

	void computeAllocationMatrix ();

	Propeller getPropeller (int i) const;
	bool isReady () const {
		return flags.isReady ();
	}

public:
	Uav (int _rotorsNumber):
		propellers(_rotorsNumber),
		rotorsNumber(_rotorsNumber)
	{
		allocationMatrix.resize (Eigen::NoChange, rotorsNumber);
		flags.addFlag ("set_up", true);
	}

	void setPropeller (int i, const Propeller &propeller);
	void setup ();

	// Force in body frame
	Eigen::VectorXd allocate (const Eigen::Vector3d &force, const Eigen::Vector3d &moment) const;

};

#define QUAD_PROP_N 4
#define HEX_PROP_N 6

class Quadrotor : public Uav
{
public:
	Quadrotor ():
		Uav (QUAD_PROP_N)
	{}
};

#endif // UAV_H
