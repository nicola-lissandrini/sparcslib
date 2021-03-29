#ifndef SPARCS_PLUGIN_H
#define SPARCS_PLUGIN_H

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

template<typename T>
T sdfParam (sdf::ElementPtr _sdf, string name, T defaultValue = T())
{
	if (!_sdf->HasElement (name))
		return _sdf->GetElement (name)->Get<T> ();
	else
		return defaultValue;
}

bool sdfCheckElement (sdf::ElementPtr _sdf, string name) {
	if (!_sdf->HasElement (name)) {
		gzerr << "Missing element <" << name << ">. Plugin not loaded" << endl;
	}
}


#endif // SPARCS_PLUGIN_H
