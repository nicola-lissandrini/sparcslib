#ifndef PORTABLE_WORDSIZES
#ifdef __MW_TARGET_USE_HARDWARE_RESOURCES_H__
#ifndef __MW_TARGET_HARDWARE_RESOURCES_H__
#define __MW_TARGET_HARDWARE_RESOURCES_H__

#define MW_MULTI_TASKING_MODE 0

#define MW_USECODERTARGET 1
#define MW_TARGETHARDWARE Robot Operating System (ROS)
#define MW_CONNECTIONINFO_TCPIP_IPADDRESS robotics.codertarget.internal.DeviceParameters.getDeviceAddress
#define MW_CONNECTIONINFO_TCPIP_PORT 17725
#define MW_CONNECTIONINFO_TCPIP_VERBOSE 0
#define MW_CONNECTIONINFO_TCPIP_RUNINBACKGROUND 1
#define MW_EXTMODE_CONFIGURATION TCP/IP
#define MW_RTOS Linux
#define MW_RTOSBASERATETASKPRIORITY 40
#define MW_DETECTTASKOVERRUNS 0.000000
#define MW_SCHEDULER_INTERRUPT_SOURCE 0
#define MW_PACKAGING_MAINTAINERNAME ROS User
#define MW_PACKAGING_MAINTAINEREMAIL rosuser@test.com
#define MW_PACKAGING_LICENSE BSD
#define MW_PACKAGING_VERSION 1.0.0
#define MW_BOARDPARAMETERS_DEVICEADDRESS 127.0.0.1
#define MW_BOARDPARAMETERS_USERNAME nicola
#define MW_RUNTIME_BUILDACTION 0
#define MW_ROS_INSTALL /opt/ros/melodic
#define MW_ROS_CATKINWS ~/ros/generic_ws
#define MW_ROS_ROSTIMESTEPPING 1
#define MW_ROS_ROSTIMENOTIFICATION 48
#define MW_ROS_STEPNOTIFY /step_notify
#define MW_DATAVERSION 2016.02

#endif /* __MW_TARGET_HARDWARE_RESOURCES_H__ */

#endif

#endif
