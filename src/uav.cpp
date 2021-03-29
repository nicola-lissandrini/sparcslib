#include "uav.h"

using namespace std;
using namespace Eigen;
using namespace XmlRpc;


Propeller::Propeller(string _name,
					 double _thrustFactor,
					 double _dragFactor,
					 double _dragSign,
					 Isometry3d _pose):
	name(_name),
	thrustFactor(_thrustFactor),
	dragFactor(_dragFactor),
	dragSign(_dragSign),
	pose(_pose)
{}

Propeller::Propeller(string _name,
					 double _thrustFactor,
					 double _dragFactor,
					 double _dragSign,
					 Vector3d _position,
					 Quaterniond _orientation):
	Propeller (_name,
			   _thrustFactor,
			   _dragFactor,
			   _dragSign,
			   Eigen::Translation3d (_position) * _orientation)
{}

Propeller::Propeller(std::string _name,
					 double _thrustFactor,
					 double _dragFactor,
					 double _dragSign,
					 Vector3d _position,
					 double _roll, double _pitch, double _yaw):
	Propeller (_name,
			   _thrustFactor,
			   _dragFactor,
			   _dragSign,
			   _position,
			   // TODO: CHECK PRODUCT ORDER
			   AngleAxisd (_yaw, Vector3d::UnitX ()) *
			   AngleAxisd (_pitch, Vector3d::UnitY ()) *
			   AngleAxisd (_roll, Vector3d::UnitZ ()))
{}


void Uav::computeAllocationMatrix()
{
	int i = 0;
	for (Propeller propeller : propellers) {
		Matrix3d rotationMatrix = propeller.pose.rotation ();
		Vector3d position = propeller.pose.translation ();
		Vector3d axis = rotationMatrix * Vector3d::UnitZ ();


		allocationMatrix.template block<D3, 1> (0, i) = propeller.thrustFactor * axis;
		allocationMatrix.template block<D3, 1> (3, i) = propeller.thrustFactor * position.cross (axis)
				+ propeller.dragSign * propeller.dragFactor * axis;
		std::cout << position  << " aaA " << propeller.dragSign << "\nbubu\n" << endl;
		i++;
	}
}

Propeller Uav::getPropeller (int i) const {
	return propellers[i];
}

void Uav::setPropeller(int i, const Propeller &propeller) {
	propellers[i] = propeller;
}

void Uav::setup() {
	computeAllocationMatrix ();
	flags.set ("set_up");
}

VectorXd Uav::allocate (const Vector3d &force, const Eigen::Vector3d &moment) const
{
	assert (isReady () && "Allocation before initialization");

	VectorXd speeds(rotorsNumber);
	VectorXd generalizedForce(2 * D3);

	generalizedForce.head<D3> () = force;
	generalizedForce.tail<D3> () = moment;

	speeds = allocationMatrix.colPivHouseholderQr ().solve (generalizedForce);
	speeds = speeds.cwiseMax (VectorXd::Zero (speeds.size ())).cwiseSqrt ();

	return speeds;
}

































