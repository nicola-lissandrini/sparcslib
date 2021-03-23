#include "force_control.h"

using namespace ros;
using namespace std;
using namespace gazebo;
using namespace physics;
using namespace ignition::math;

void ForceControl::Load (ModelPtr _model, sdf::ElementPtr _sdf)
{
	string linkName, forceTopicName, odomTopicName;
	model = _model;

	if (!_sdf->HasElement ("link")) {
		gzerr << "Missing <link> element. Plugin not loaded." << endl;
		return;
	}

	linkName = _sdf->GetElement ("link")->Get<string> ();

	if (!_sdf->HasElement ("force_topic"))
		forceTopicName = "command/wrench";
	else
		forceTopicName = _sdf->GetElement ("force_topic")->Get<string> ();


	if (!_sdf->HasElement ("odom_topic"))
		odomTopicName = "odometry";
	else
		odomTopicName = _sdf->GetElement ("odom_topic")->Get<string> ();

	link = boost::dynamic_pointer_cast<Link> (_model->GetByName (linkName));

	applyToWorldFrame = true;
	if (_sdf->HasElement ("frame")) {
		string frameName = _sdf->GetElement ("frame")->Get<string> ();

		if (frameName == "local")
			applyToWorldFrame = false;
		else {
			if (frameName != "local")
				gzerr << "Frame specification can be either 'world' or 'local'. Defaulting to 'world'.";
		}
	}

	// Init ROS
	if (!ros::isInitialized ()) {
		int argc = 0;
		char **argv = NULL;

		ros::init (argc, argv, NODE_NAME);
	}

	rosNode = new NodeHandle (NODE_NAME);
	rosNode->setCallbackQueue (&rosQueue);

	SubscribeOptions so =
			SubscribeOptions::create<geometry_msgs::Wrench> (forceTopicName, 1,
															 boost::bind(&ForceControl::forceCallback, this, _1),
															 ros::VoidPtr (), &rosQueue);
	forceSub = rosNode->subscribe (so);
	odomPub = rosNode->advertise<nav_msgs::Odometry> (odomTopicName, 1);

	rosQueueThread = thread (bind (&ForceControl::queueThread, this));

	updateConnection = event::Events::ConnectWorldUpdateBegin (
				boost::bind(&ForceControl::OnUpdate, this, _1));

	seq = 0;
}

void ForceControl::forceCallback (const geometry_msgs::WrenchConstPtr &wrenchMsg)
{
	currForce = Vector3d (wrenchMsg->force.x,
						  wrenchMsg->force.y,
						  wrenchMsg->force.z);
	currTorque = Vector3d (wrenchMsg->torque.x,
						   wrenchMsg->torque.y,
						   wrenchMsg->torque.z);
}

void ForceControl::publishOdometry (const Pose3d &pose, const Vector3d &linearVel, const Vector3d &angularVel)
{
	nav_msgs::Odometry odom;

	odom.header.frame_id = link->GetParent ()->GetName ();
	odom.header.seq = seq;
	odom.header.stamp = Time::now ();
	odom.child_frame_id = link->GetName ();
	odom.pose.pose.position.x = pose.Pos ().X ();
	odom.pose.pose.position.y = pose.Pos ().Y ();
	odom.pose.pose.position.z = pose.Pos ().Z ();
	odom.pose.pose.orientation.x = pose.Rot ().X ();
	odom.pose.pose.orientation.y = pose.Rot ().Y ();
	odom.pose.pose.orientation.z = pose.Rot ().Z ();
	odom.pose.pose.orientation.w = pose.Rot ().W ();
	odom.twist.twist.linear.x = linearVel.X ();
	odom.twist.twist.linear.y = linearVel.Y ();
	odom.twist.twist.linear.z = linearVel.Z ();
	odom.twist.twist.angular.x = angularVel.X ();
	odom.twist.twist.angular.y = angularVel.Y ();
	odom.twist.twist.angular.z = angularVel.Z ();

	odomPub.publish (odom);

	seq++;
}

void ForceControl::OnUpdate (const common::UpdateInfo &_info)
{
	Pose3d linkPose = link->WorldPose ();
	Vector3d linkLinearVel = link->WorldLinearVel ();
	Vector3d linkAngularVel = link->WorldAngularVel ();

	publishOdometry (linkPose, linkLinearVel, linkAngularVel);

	if (applyToWorldFrame) {
		link->AddForce (currForce);
		link->AddTorque (currTorque);
	} else {
		link->AddRelativeForce (currForce);
		link->AddRelativeTorque (currTorque);
	}
}

void ForceControl::queueThread () {
	static const double timeout = 0.01;
	while (rosNode->ok ()) {
		rosQueue.callAvailable (WallDuration(timeout));
	}
}

GZ_REGISTER_MODEL_PLUGIN(ForceControl)


















