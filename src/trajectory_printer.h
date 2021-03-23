#ifndef TRAJECTORY_PRINTER_H
#define TRAJECTORY_PRINTER_H


#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/rendering/DynamicLines.hh>
#include <gazebo/rendering/RenderTypes.hh>
#include <gazebo/rendering/Visual.hh>
#include <gazebo/rendering/Scene.hh>

#include <ros/ros.h>
#include <ros/callback_queue.h>
#include <ros/subscribe_options.h>

#include <nav_msgs/Path.h>

#include <thread>
#include <map>

#include "sparcsnode.h"

namespace gazebo {

namespace rendering {

class TrajectoryPrinter : public VisualPlugin
{
	ros::NodeHandle *rosNode;
	ros::CallbackQueue rosQueue;
	ros::Subscriber trajectorySub;
	std::thread rosQueueThread;
	std::string topicName;
	rendering::VisualPtr visual;
	ScenePtr scene;
	event::ConnectionPtr updateConnection;

	nav_msgs::Path pathDataMsg;
	DynamicLines *line;
	ReadyFlags<std::string> readyFlags;

	void drawLine ();
	void queueThread ();

	bool processSdf (sdf::ElementPtr sdf);

protected:
	virtual void UpdateChild ();

public:
	TrajectoryPrinter ():
		VisualPlugin ()
	{}

	void Load (VisualPtr _visual, sdf::ElementPtr _sdf);
	void trajectoryCallback (const nav_msgs::PathConstPtr &newTrajectory);
};

}
}

#endif // TRAJECTORY_PRINTER_H
