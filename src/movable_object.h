#ifndef MOVABLE_OBJECT_H
#define MOVABLE_OBJECT_H

#include <gazebo/gazebo.hh>

#include <gazebo/gazebo_client.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <ignition/math.hh>
#include <ros/ros.h>
#include <ros/callback_queue.h>
#include <ros/subscribe_options.h>
#include <thread>

#include <geometry_msgs/Pose.h>

#ifndef NODE_NAME
# define NODE_NAME "target_trajectory"
#endif
#include "sparcsnode.h"

namespace gazebo {

class MovableObject : public ModelPlugin
{
	physics::ModelPtr model;
	physics::LinkPtr link;
	ros::NodeHandle *rosNode;
	ros::Subscriber poseSub;
	std::thread rosQueueThread;
	ros::CallbackQueue rosQueue;
	event::ConnectionPtr updateConnection;

	ignition::math::Pose3d newPose;
	ReadyFlags<std::string> flags;

	void queueThread ();

public:
	MovableObject( ):
		ModelPlugin ()
	{}

	void Load (physics::ModelPtr _model, sdf::ElementPtr _sdf);
	void OnUpdate ();

	void poseCallback (const geometry_msgs::PoseConstPtr &newPoseMsg);
};

}

#endif // MOVABLE_OBJECT_H
