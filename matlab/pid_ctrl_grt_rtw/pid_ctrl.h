/*
 * pid_ctrl.h
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

#ifndef RTW_HEADER_pid_ctrl_h_
#define RTW_HEADER_pid_ctrl_h_
#include <float.h>
#include <string.h>
#include <stddef.h>
#ifndef pid_ctrl_COMMON_INCLUDES_
# define pid_ctrl_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "slros_initialize.h"
#endif                                 /* pid_ctrl_COMMON_INCLUDES_ */

#include "pid_ctrl_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               (&(rtm)->Timing.taskTime0)
#endif

/* Block signals (default storage) */
typedef struct {
  SL_Bus_pid_ctrl_nav_msgs_Odometry In1;/* '<S8>/In1' */
} B_pid_ctrl_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  robotics_slros_internal_block_T obj; /* '<S6>/SinkBlock' */
  robotics_slros_internal_blo_k_T obj_n;/* '<S7>/SourceBlock' */
  robotics_slros_internal_bl_k1_T obj_m;/* '<S10>/ServiceCaller' */
  real_T DiscreteTimeIntegrator_DSTATE[3];/* '<Root>/Discrete-Time Integrator' */
  real_T UD_DSTATE[3];                 /* '<S1>/UD' */
  struct {
    void *LoggedData;
  } Scope_PWORK;                       /* '<Root>/Scope' */

  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<Root>/Scope1' */

  struct {
    void *LoggedData;
  } Scope2_PWORK;                      /* '<Root>/Scope2' */

  ExampleHelperSimulationRateCo_T obj_e;/* '<Root>/Simulation Rate Control' */
  boolean_T objisempty;                /* '<S10>/ServiceCaller' */
  boolean_T objisempty_g;              /* '<S7>/SourceBlock' */
  boolean_T objisempty_e;              /* '<S6>/SinkBlock' */
  boolean_T objisempty_h;              /* '<Root>/Simulation Rate Control' */
  boolean_T ResetWorld_MODE;           /* '<Root>/Reset World' */
} DW_pid_ctrl_T;

/* Parameters (default storage) */
struct P_pid_ctrl_T_ {
  real_T Ts;                           /* Variable: Ts
                                        * Referenced by: '<Root>/Step'
                                        */
  real_T DiscreteDerivative_ICPrevScaled;
                              /* Mask Parameter: DiscreteDerivative_ICPrevScaled
                               * Referenced by: '<S1>/UD'
                               */
  SL_Bus_pid_ctrl_nav_msgs_Odometry Out1_Y0;/* Computed Parameter: Out1_Y0
                                             * Referenced by: '<S8>/Out1'
                                             */
  SL_Bus_pid_ctrl_nav_msgs_Odometry Constant_Value;/* Computed Parameter: Constant_Value
                                                    * Referenced by: '<S7>/Constant'
                                                    */
  SL_Bus_pid_ctrl_geometry_msgs_Wrench Constant_Value_j;/* Computed Parameter: Constant_Value_j
                                                         * Referenced by: '<S5>/Constant'
                                                         */
  SL_Bus_pid_ctrl_std_srvs_EmptyRequest Constant_Value_a;/* Computed Parameter: Constant_Value_a
                                                          * Referenced by: '<S9>/Constant'
                                                          */
  SL_Bus_pid_ctrl_std_srvs_EmptyResponse Constant_Value_m;/* Computed Parameter: Constant_Value_m
                                                           * Referenced by: '<S10>/Constant'
                                                           */
  real_T Planelimit_Value[3];          /* Expression: [0, 0, 0.1]
                                        * Referenced by: '<Root>/Plane limit'
                                        */
  real_T Planelimit1_Value[3];         /* Expression: [0, 0, 1]
                                        * Referenced by: '<Root>/Plane limit1'
                                        */
  real_T Gain_Gain;                    /* Expression: 10
                                        * Referenced by: '<Root>/Gain'
                                        */
  real_T DiscreteTimeIntegrator_gainval;
                           /* Computed Parameter: DiscreteTimeIntegrator_gainval
                            * Referenced by: '<Root>/Discrete-Time Integrator'
                            */
  real_T DiscreteTimeIntegrator_IC;    /* Expression: 0
                                        * Referenced by: '<Root>/Discrete-Time Integrator'
                                        */
  real_T Gain2_Gain;                   /* Expression: 10
                                        * Referenced by: '<Root>/Gain2'
                                        */
  real_T TSamp_WtEt;                   /* Computed Parameter: TSamp_WtEt
                                        * Referenced by: '<S1>/TSamp'
                                        */
  real_T Gravitycompensation_Value[3]; /* Expression: [0, 0, mass*g]
                                        * Referenced by: '<Root>/Gravity compensation'
                                        */
  real_T Gain1_Gain;                   /* Expression: 0.1
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real_T Step_Y0;                      /* Expression: 1
                                        * Referenced by: '<Root>/Step'
                                        */
  real_T Step_YFinal;                  /* Expression: 0
                                        * Referenced by: '<Root>/Step'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_pid_ctrl_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_pid_ctrl_T pid_ctrl_P;

/* Block signals (default storage) */
extern B_pid_ctrl_T pid_ctrl_B;

/* Block states (default storage) */
extern DW_pid_ctrl_T pid_ctrl_DW;

/* Model entry point functions */
extern void pid_ctrl_initialize(void);
extern void pid_ctrl_step(void);
extern void pid_ctrl_terminate(void);

/* Real-time Model object */
extern RT_MODEL_pid_ctrl_T *const pid_ctrl_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'pid_ctrl'
 * '<S1>'   : 'pid_ctrl/Discrete Derivative'
 * '<S2>'   : 'pid_ctrl/ROS Command out'
 * '<S3>'   : 'pid_ctrl/ROS state IN'
 * '<S4>'   : 'pid_ctrl/Reset World'
 * '<S5>'   : 'pid_ctrl/ROS Command out/Blank Message'
 * '<S6>'   : 'pid_ctrl/ROS Command out/Publish'
 * '<S7>'   : 'pid_ctrl/ROS state IN/Subscribe'
 * '<S8>'   : 'pid_ctrl/ROS state IN/Subscribe/Enabled Subsystem'
 * '<S9>'   : 'pid_ctrl/Reset World/Blank Message1'
 * '<S10>'  : 'pid_ctrl/Reset World/Call Service'
 */
#endif                                 /* RTW_HEADER_pid_ctrl_h_ */
