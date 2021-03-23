#include "trajectory_printer.h"


using namespace gazebo;
using namespace gazebo::rendering;
using namespace physics;
using namespace ignition::math;
using namespace ros;
using namespace std;

void TrajectoryPrinter::Load (VisualPtr _visual, sdf::ElementPtr _sdf)
{
	visual = _visual;

	if (!processSdf (_sdf))
		return;

	if (!ros::isInitialized ()) {
		int argc = 0;
		char **argv = NULL;

		ros::init (argc, argv, "prediction_printer");
	}

	rosNode = new NodeHandle ("gazebo_client");
	rosNode->setCallbackQueue (&rosQueue);
	SubscribeOptions so =
			SubscribeOptions::create<nav_msgs::Path> (topicName, 1,
													  boost::bind(&TrajectoryPrinter::trajectoryCallback, this, _1),
													  ros::VoidPtr (), &rosQueue);
	trajectorySub = rosNode->subscribe (so);
	rosQueueThread = thread (bind (&TrajectoryPrinter::queueThread, this));
	updateConnection = event::Events::ConnectRender (
				boost::bind (&TrajectoryPrinter::UpdateChild, this));

	readyFlags.addFlag ("new_msg");
}

bool TrajectoryPrinter::processSdf (sdf::ElementPtr sdf)
{
	if (!sdf->HasElement ("topic")) {
		gzerr << "Missing sdf element <topic>. Plugin not loaded." << endl;
		return false;
	}

	topicName = sdf->GetElement ("topic")->GetValue ()->GetAsString ();

	return true;
}

void TrajectoryPrinter::trajectoryCallback (const nav_msgs::PathConstPtr &newTrajectory) {
	readyFlags.set ("new_msg");
	pathDataMsg = *newTrajectory;
}

void TrajectoryPrinter::queueThread () {
	static const double timeout = 0.01;
	while (rosNode->ok ()) {
		rosQueue.callAvailable (WallDuration(timeout));
	}
}

void TrajectoryPrinter::UpdateChild () {
	// Only update when new data is available
	if (!readyFlags.isReady ())
		return;

	drawLine ();
	readyFlags.setProcessed ();
}

void TrajectoryPrinter::drawLine ()
{
	auto poses = pathDataMsg.poses;

	visual->DeleteDynamicLine (line);
	line = visual->CreateDynamicLine ();

	for (nav_msgs::Path::_poses_type::iterator it = poses.begin (); it != poses.end (); it++) {
		geometry_msgs::PoseStamped curr = *it;
		line->AddPoint (curr.pose.position.x,
						   curr.pose.position.y,
						   curr.pose.position.z);
	}

	line->setMaterial ("Gazebo/Black");
	line->setVisibilityFlags (GZ_VISIBILITY_ALL);

	visual->SetVisible (true);
}

GZ_REGISTER_VISUAL_PLUGIN(TrajectoryPrinter)












