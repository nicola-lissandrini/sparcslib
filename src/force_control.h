#ifndef FORCE_CONTROL_H
#define FORCE_CONTROL_H

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

#include <geometry_msgs/Wrench.h>
#include <nav_msgs/Odometry.h>

#ifndef NODE_NAME
# define NODE_NAME "force_control"
#endif
#include "sparcsnode.h"

namespace gazebo {

class ForceControl : public ModelPlugin
{
	physics::ModelPtr model;
	physics::LinkPtr link;
	ros::NodeHandle *rosNode;
	ros::Subscriber forceSub;
	ros::Publisher odomPub;
	std::thread rosQueueThread;
	ros::CallbackQueue rosQueue;
	event::ConnectionPtr updateConnection;
	int seq;

	bool applyToWorldFrame;
	ignition::math::Vector3d currForce, currTorque;

	void queueThread ();
	void OnUpdate(const common::UpdateInfo& _info);
	void publishOdometry(const ignition::math::Pose3d &pose, const ignition::math::Vector3d &linearVel, const ignition::math::Vector3d &angularVel);


public:
	ForceControl():
		ModelPlugin ()
	{}

	void Load (physics::ModelPtr _model, sdf::ElementPtr _sdf);
	void forceCallback (const geometry_msgs::WrenchConstPtr &wrenchMsg);
};

}

#endif // FORCE_CONTROL_H
