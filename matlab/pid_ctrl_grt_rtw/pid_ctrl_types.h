/*
 * pid_ctrl_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "pid_ctrl".
 *
 * Model version              : 1.2
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C source code generated on : Mon Sep 16 17:56:24 2019
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_pid_ctrl_types_h_
#define RTW_HEADER_pid_ctrl_types_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_geometry_msgs_Vector3_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_geometry_msgs_Vector3_

typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
} SL_Bus_pid_ctrl_geometry_msgs_Vector3;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_geometry_msgs_Wrench_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_geometry_msgs_Wrench_

typedef struct {
  SL_Bus_pid_ctrl_geometry_msgs_Vector3 Force;
  SL_Bus_pid_ctrl_geometry_msgs_Vector3 Torque;
} SL_Bus_pid_ctrl_geometry_msgs_Wrench;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_

typedef struct {
  uint32_T CurrentLength;
  uint32_T ReceivedLength;
} SL_Bus_ROSVariableLengthArrayInfo;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_ros_time_Time_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_ros_time_Time_

typedef struct {
  real_T Sec;
  real_T Nsec;
} SL_Bus_pid_ctrl_ros_time_Time;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_std_msgs_Header_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_std_msgs_Header_

typedef struct {
  uint32_T Seq;
  uint8_T FrameId[128];
  SL_Bus_ROSVariableLengthArrayInfo FrameId_SL_Info;
  SL_Bus_pid_ctrl_ros_time_Time Stamp;
} SL_Bus_pid_ctrl_std_msgs_Header;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_geometry_msgs_Point_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_geometry_msgs_Point_

typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
} SL_Bus_pid_ctrl_geometry_msgs_Point;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_geometry_msgs_Quaternion_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_geometry_msgs_Quaternion_

typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
  real_T W;
} SL_Bus_pid_ctrl_geometry_msgs_Quaternion;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_geometry_msgs_Pose_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_geometry_msgs_Pose_

typedef struct {
  SL_Bus_pid_ctrl_geometry_msgs_Point Position;
  SL_Bus_pid_ctrl_geometry_msgs_Quaternion Orientation;
} SL_Bus_pid_ctrl_geometry_msgs_Pose;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_geometry_msgs_PoseWithCovariance_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_geometry_msgs_PoseWithCovariance_

typedef struct {
  real_T Covariance[36];
  SL_Bus_pid_ctrl_geometry_msgs_Pose Pose;
} SL_Bus_pid_ctrl_geometry_msgs_PoseWithCovariance;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_geometry_msgs_Twist_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_geometry_msgs_Twist_

typedef struct {
  SL_Bus_pid_ctrl_geometry_msgs_Vector3 Linear;
  SL_Bus_pid_ctrl_geometry_msgs_Vector3 Angular;
} SL_Bus_pid_ctrl_geometry_msgs_Twist;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_geometry_msgs_TwistWithCovariance_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_geometry_msgs_TwistWithCovariance_

typedef struct {
  real_T Covariance[36];
  SL_Bus_pid_ctrl_geometry_msgs_Twist Twist;
} SL_Bus_pid_ctrl_geometry_msgs_TwistWithCovariance;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_nav_msgs_Odometry_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_nav_msgs_Odometry_

typedef struct {
  uint8_T ChildFrameId[128];
  SL_Bus_ROSVariableLengthArrayInfo ChildFrameId_SL_Info;
  SL_Bus_pid_ctrl_std_msgs_Header Header;
  SL_Bus_pid_ctrl_geometry_msgs_PoseWithCovariance Pose;
  SL_Bus_pid_ctrl_geometry_msgs_TwistWithCovariance Twist;
} SL_Bus_pid_ctrl_nav_msgs_Odometry;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_std_srvs_EmptyRequest_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_std_srvs_EmptyRequest_

typedef struct {
  boolean_T SL_DummyData;
} SL_Bus_pid_ctrl_std_srvs_EmptyRequest;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_std_srvs_EmptyResponse_
#define DEFINED_TYPEDEF_FOR_SL_Bus_pid_ctrl_std_srvs_EmptyResponse_

typedef struct {
  boolean_T SL_DummyData;
} SL_Bus_pid_ctrl_std_srvs_EmptyResponse;

#endif

#ifndef typedef_ExampleHelperSimulationRateCo_T
#define typedef_ExampleHelperSimulationRateCo_T

typedef struct {
  int32_T isInitialized;
} ExampleHelperSimulationRateCo_T;

#endif                               /*typedef_ExampleHelperSimulationRateCo_T*/

#ifndef typedef_robotics_slros_internal_block_T
#define typedef_robotics_slros_internal_block_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
} robotics_slros_internal_block_T;

#endif                               /*typedef_robotics_slros_internal_block_T*/

#ifndef typedef_robotics_slros_internal_blo_k_T
#define typedef_robotics_slros_internal_blo_k_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
} robotics_slros_internal_blo_k_T;

#endif                               /*typedef_robotics_slros_internal_blo_k_T*/

#ifndef typedef_robotics_slros_internal_bl_k1_T
#define typedef_robotics_slros_internal_bl_k1_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
} robotics_slros_internal_bl_k1_T;

#endif                               /*typedef_robotics_slros_internal_bl_k1_T*/

#ifndef typedef_struct_T_pid_ctrl_T
#define typedef_struct_T_pid_ctrl_T

typedef struct {
  char_T Value[6];
} struct_T_pid_ctrl_T;

#endif                                 /*typedef_struct_T_pid_ctrl_T*/

#ifndef typedef_b_struct_T_pid_ctrl_T
#define typedef_b_struct_T_pid_ctrl_T

typedef struct {
  char_T Value[3];
} b_struct_T_pid_ctrl_T;

#endif                                 /*typedef_b_struct_T_pid_ctrl_T*/

#ifndef typedef_c_robotics_slros_internal_blo_T
#define typedef_c_robotics_slros_internal_blo_T

typedef uint8_T c_robotics_slros_internal_blo_T;

#endif                               /*typedef_c_robotics_slros_internal_blo_T*/

#ifndef c_robotics_slros_internal_block_constants
#define c_robotics_slros_internal_block_constants

/* enum c_robotics_slros_internal_block */
#define SLSuccess                      ((c_robotics_slros_internal_blo_T)0U)
#define SLConnectionTimeout            ((c_robotics_slros_internal_blo_T)1U)
#define SLCallFailure                  ((c_robotics_slros_internal_blo_T)2U)
#define SLOtherError                   ((c_robotics_slros_internal_blo_T)3U)
#endif                             /*c_robotics_slros_internal_block_constants*/

/* Parameters (default storage) */
typedef struct P_pid_ctrl_T_ P_pid_ctrl_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_pid_ctrl_T RT_MODEL_pid_ctrl_T;

#endif                                 /* RTW_HEADER_pid_ctrl_types_h_ */
