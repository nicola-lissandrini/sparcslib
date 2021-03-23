//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: sparcslib_types.h
//
// Code generated for Simulink model 'sparcslib'.
//
// Model version                  : 1.4
// Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
// C/C++ source code generated on : Tue Sep 17 15:55:55 2019
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Emulation hardware selection:
//    Differs from embedded hardware (MATLAB Host)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_sparcslib_types_h_
#define RTW_HEADER_sparcslib_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_geometry_msgs_Vector3_
#define DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_geometry_msgs_Vector3_

// MsgType=geometry_msgs/Vector3
typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
} SL_Bus_sparcslib_geometry_msgs_Vector3;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_geometry_msgs_Wrench_
#define DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_geometry_msgs_Wrench_

// MsgType=geometry_msgs/Wrench
typedef struct {
  // MsgType=geometry_msgs/Vector3
  SL_Bus_sparcslib_geometry_msgs_Vector3 Force;

  // MsgType=geometry_msgs/Vector3
  SL_Bus_sparcslib_geometry_msgs_Vector3 Torque;
} SL_Bus_sparcslib_geometry_msgs_Wrench;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_

typedef struct {
  uint32_T CurrentLength;
  uint32_T ReceivedLength;
} SL_Bus_ROSVariableLengthArrayInfo;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_ros_time_Time_
#define DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_ros_time_Time_

// MsgType=ros_time/Time
typedef struct {
  real_T Sec;
  real_T Nsec;
} SL_Bus_sparcslib_ros_time_Time;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_std_msgs_Header_
#define DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_std_msgs_Header_

// MsgType=std_msgs/Header
typedef struct {
  uint32_T Seq;

  // PrimitiveROSType=string:IsVarLen=1:VarLenCategory=data:VarLenElem=FrameId_SL_Info:TruncateAction=warn 
  uint8_T FrameId[128];

  // IsVarLen=1:VarLenCategory=length:VarLenElem=FrameId
  SL_Bus_ROSVariableLengthArrayInfo FrameId_SL_Info;

  // MsgType=ros_time/Time
  SL_Bus_sparcslib_ros_time_Time Stamp;
} SL_Bus_sparcslib_std_msgs_Header;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_geometry_msgs_Point_
#define DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_geometry_msgs_Point_

// MsgType=geometry_msgs/Point
typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
} SL_Bus_sparcslib_geometry_msgs_Point;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_geometry_msgs_Quaternion_
#define DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_geometry_msgs_Quaternion_

// MsgType=geometry_msgs/Quaternion
typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
  real_T W;
} SL_Bus_sparcslib_geometry_msgs_Quaternion;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_geometry_msgs_Pose_
#define DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_geometry_msgs_Pose_

// MsgType=geometry_msgs/Pose
typedef struct {
  // MsgType=geometry_msgs/Point
  SL_Bus_sparcslib_geometry_msgs_Point Position;

  // MsgType=geometry_msgs/Quaternion
  SL_Bus_sparcslib_geometry_msgs_Quaternion Orientation;
} SL_Bus_sparcslib_geometry_msgs_Pose;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_geometry_msgs_PoseWithCovariance_
#define DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_geometry_msgs_PoseWithCovariance_

// MsgType=geometry_msgs/PoseWithCovariance
typedef struct {
  real_T Covariance[36];

  // MsgType=geometry_msgs/Pose
  SL_Bus_sparcslib_geometry_msgs_Pose Pose;
} SL_Bus_sparcslib_geometry_msgs_PoseWithCovariance;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_geometry_msgs_Twist_
#define DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_geometry_msgs_Twist_

// MsgType=geometry_msgs/Twist
typedef struct {
  // MsgType=geometry_msgs/Vector3
  SL_Bus_sparcslib_geometry_msgs_Vector3 Linear;

  // MsgType=geometry_msgs/Vector3
  SL_Bus_sparcslib_geometry_msgs_Vector3 Angular;
} SL_Bus_sparcslib_geometry_msgs_Twist;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_geometry_msgs_TwistWithCovariance_
#define DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_geometry_msgs_TwistWithCovariance_

// MsgType=geometry_msgs/TwistWithCovariance
typedef struct {
  real_T Covariance[36];

  // MsgType=geometry_msgs/Twist
  SL_Bus_sparcslib_geometry_msgs_Twist Twist;
} SL_Bus_sparcslib_geometry_msgs_TwistWithCovariance;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_nav_msgs_Odometry_
#define DEFINED_TYPEDEF_FOR_SL_Bus_sparcslib_nav_msgs_Odometry_

// MsgType=nav_msgs/Odometry
typedef struct {
  // PrimitiveROSType=string:IsVarLen=1:VarLenCategory=data:VarLenElem=ChildFrameId_SL_Info:TruncateAction=warn 
  uint8_T ChildFrameId[128];

  // IsVarLen=1:VarLenCategory=length:VarLenElem=ChildFrameId
  SL_Bus_ROSVariableLengthArrayInfo ChildFrameId_SL_Info;

  // MsgType=std_msgs/Header
  SL_Bus_sparcslib_std_msgs_Header Header;

  // MsgType=geometry_msgs/PoseWithCovariance
  SL_Bus_sparcslib_geometry_msgs_PoseWithCovariance Pose;

  // MsgType=geometry_msgs/TwistWithCovariance
  SL_Bus_sparcslib_geometry_msgs_TwistWithCovariance Twist;
} SL_Bus_sparcslib_nav_msgs_Odometry;

#endif

#ifndef typedef_robotics_slros_internal_block_Publisher_sparcslib_T
#define typedef_robotics_slros_internal_block_Publisher_sparcslib_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
} robotics_slros_internal_block_Publisher_sparcslib_T;

#endif             //typedef_robotics_slros_internal_block_Publisher_sparcslib_T

#ifndef typedef_robotics_slros_internal_block_Subscriber_sparcslib_T
#define typedef_robotics_slros_internal_block_Subscriber_sparcslib_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
} robotics_slros_internal_block_Subscriber_sparcslib_T;

#endif            //typedef_robotics_slros_internal_block_Subscriber_sparcslib_T

// Parameters (default storage)
typedef struct P_sparcslib_T_ P_sparcslib_T;

// Forward declaration for rtModel
typedef struct tag_RTM_sparcslib_T RT_MODEL_sparcslib_T;

#endif                                 // RTW_HEADER_sparcslib_types_h_

//
// File trailer for generated code.
//
// [EOF]
//
