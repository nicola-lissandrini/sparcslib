#include "movable_object.h"

using namespace ros;
using namespace std;
using namespace gazebo;
using namespace physics;
using namespace ignition::math;

void MovableObject::Load(gazebo::physics::ModelPtr _model, sdf::ElementPtr _sdf)
{
	string linkName, topicName;
	model = _model;

	if (!_sdf->HasElement ("link")) {
		gzerr << "Missing <link> element. Plugin not loaded." << endl;
		return;
	}
	if (!_sdf->HasElement ("topic")) {
		gzerr << "Missing sdf element <topic>. Plugin not loaded." << endl;
		return;
	}

	linkName = _sdf->GetElement ("link")->Get<string> ();
	topicName = _sdf->GetElement ("topic")->Get<string> ();

	link = boost::dynamic_pointer_cast<Link> (_model->GetByName (linkName));

	// Init ROS
	if (!ros::isInitialized ()) {
		int argc = 0;
		char **argv = NULL;

		ros::init (argc, argv, "prediction_printer");
	}

	rosNode = new NodeHandle ("gazebo_client");
	rosNode->setCallbackQueue (&rosQueue);

	SubscribeOptions so =
			SubscribeOptions::create<geometry_msgs::Pose> (topicName, 1,
														   boost::bind(&MovableObject::poseCallback, this, _1),
														   ros::VoidPtr (), &rosQueue);
	poseSub = rosNode->subscribe (so);
	rosQueueThread = thread (bind (&MovableObject::queueThread, this));

	this->updateConnection = event::Events::ConnectBeforePhysicsUpdate(
				std::bind(&MovableObject::OnUpdate, this));

	flags.addFlag ("new_msg");
}

void MovableObject::poseCallback (const geometry_msgs::PoseConstPtr &newPoseMsg)
{
	newPose.Set (Vector3d (
					 newPoseMsg->position.x,
					 newPoseMsg->position.y,
					 newPoseMsg->position.z),
				 Quaterniond (
					 newPoseMsg->orientation.w,
					 newPoseMsg->orientation.x,
					 newPoseMsg->orientation.y,
					 newPoseMsg->orientation.z));

	flags.set ("new_msg");
}

void MovableObject::OnUpdate ()
{
	if (!flags.isReady () || flags.isProcessed ())
		return;

	link->SetWorldPose (newPose);
	flags.setProcessed ();
}

void MovableObject::queueThread () {
	static const double timeout = 0.01;
	while (rosNode->ok ()) {
		rosQueue.callAvailable (WallDuration(timeout));
	}
}

GZ_REGISTER_MODEL_PLUGIN(MovableObject)
