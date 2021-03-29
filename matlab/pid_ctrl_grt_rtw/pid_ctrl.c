/*
 * pid_ctrl.c
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

#include "pid_ctrl.h"
#include "pid_ctrl_private.h"

/* Block signals (default storage) */
B_pid_ctrl_T pid_ctrl_B;

/* Block states (default storage) */
DW_pid_ctrl_T pid_ctrl_DW;

/* Real-time model */
RT_MODEL_pid_ctrl_T pid_ctrl_M_;
RT_MODEL_pid_ctrl_T *const pid_ctrl_M = &pid_ctrl_M_;

/* Forward declaration for local functions */
static void matlabCodegenHandle_matlabCod_k(robotics_slros_internal_blo_k_T *obj);
static void matlabCodegenHandle_matlabCodeg(robotics_slros_internal_block_T *obj);
static void matlabCodegenHandle_matlabCo_k1(robotics_slros_internal_bl_k1_T *obj);
static void matlabCodegenHandle_matlabCod_k(robotics_slros_internal_blo_k_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
  }
}

static void matlabCodegenHandle_matlabCodeg(robotics_slros_internal_block_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
  }
}

static void matlabCodegenHandle_matlabCo_k1(robotics_slros_internal_bl_k1_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
  }
}

/* Model step function */
void pid_ctrl_step(void)
{
  /* local block i/o variables */
  real_T rtb_Sum2[3];
  real_T rtb_Sum[3];
  real_T rtb_Sum1[3];
  real_T currentTime;
  SL_Bus_pid_ctrl_nav_msgs_Odometry b_varargout_2;
  uint8_T b_varargout_2_0;
  SL_Bus_pid_ctrl_std_srvs_EmptyResponse b_varargout_1;
  boolean_T isCreated;
  SL_Bus_pid_ctrl_geometry_msgs_Wrench rtb_BusAssignment;
  static const char_T tmp[20] = { '/', 'g', 'a', 'z', 'e', 'b', 'o', '/', 'r',
    'e', 's', 'e', 't', '_', 'w', 'o', 'r', 'l', 'd', '\x00' };

  char_T tmp_0[20];
  int32_T i;
  real_T rtb_TSamp;
  real_T rtb_TSamp_idx_0;
  real_T rtb_TSamp_idx_1;

  /* Outputs for Atomic SubSystem: '<S3>/Subscribe' */
  /* MATLABSystem: '<S7>/SourceBlock' incorporates:
   *  Inport: '<S8>/In1'
   */
  isCreated = Sub_pid_ctrl_1.getLatestMessage(&b_varargout_2);

  /* Outputs for Enabled SubSystem: '<S7>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S8>/Enable'
   */
  if (isCreated) {
    pid_ctrl_B.In1 = b_varargout_2;
  }

  /* End of MATLABSystem: '<S7>/SourceBlock' */
  /* End of Outputs for SubSystem: '<S7>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<S3>/Subscribe' */

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Plane limit'
   */
  rtb_Sum2[0] = pid_ctrl_B.In1.Pose.Pose.Position.X -
    pid_ctrl_P.Planelimit_Value[0];
  rtb_Sum2[1] = pid_ctrl_B.In1.Pose.Pose.Position.Y -
    pid_ctrl_P.Planelimit_Value[1];
  rtb_Sum2[2] = pid_ctrl_B.In1.Pose.Pose.Position.Z -
    pid_ctrl_P.Planelimit_Value[2];

  /* Sum: '<Root>/Sum' incorporates:
   *  Constant: '<Root>/Plane limit1'
   */
  rtb_Sum[0] = pid_ctrl_P.Planelimit1_Value[0] - rtb_Sum2[0];

  /* Gain: '<Root>/Gain2' */
  rtb_Sum1[0] = pid_ctrl_P.Gain2_Gain * rtb_Sum[0];

  /* SampleTimeMath: '<S1>/TSamp'
   *
   * About '<S1>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_TSamp = rtb_Sum1[0] * pid_ctrl_P.TSamp_WtEt;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Gravity compensation'
   *  DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
   *  Gain: '<Root>/Gain'
   *  Sum: '<Root>/Sum3'
   *  Sum: '<S1>/Diff'
   *  UnitDelay: '<S1>/UD'
   */
  rtb_Sum1[0] = ((pid_ctrl_P.Gain_Gain * rtb_Sum[0] +
                  pid_ctrl_DW.DiscreteTimeIntegrator_DSTATE[0]) + (rtb_TSamp -
    pid_ctrl_DW.UD_DSTATE[0])) + pid_ctrl_P.Gravitycompensation_Value[0];

  /* SampleTimeMath: '<S1>/TSamp'
   *
   * About '<S1>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_TSamp_idx_0 = rtb_TSamp;

  /* Sum: '<Root>/Sum' incorporates:
   *  Constant: '<Root>/Plane limit1'
   */
  rtb_Sum[1] = pid_ctrl_P.Planelimit1_Value[1] - rtb_Sum2[1];

  /* Gain: '<Root>/Gain2' */
  rtb_Sum1[1] = pid_ctrl_P.Gain2_Gain * rtb_Sum[1];

  /* SampleTimeMath: '<S1>/TSamp'
   *
   * About '<S1>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_TSamp = rtb_Sum1[1] * pid_ctrl_P.TSamp_WtEt;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Gravity compensation'
   *  DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
   *  Gain: '<Root>/Gain'
   *  Sum: '<Root>/Sum3'
   *  Sum: '<S1>/Diff'
   *  UnitDelay: '<S1>/UD'
   */
  rtb_Sum1[1] = ((pid_ctrl_P.Gain_Gain * rtb_Sum[1] +
                  pid_ctrl_DW.DiscreteTimeIntegrator_DSTATE[1]) + (rtb_TSamp -
    pid_ctrl_DW.UD_DSTATE[1])) + pid_ctrl_P.Gravitycompensation_Value[1];

  /* SampleTimeMath: '<S1>/TSamp'
   *
   * About '<S1>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_TSamp_idx_1 = rtb_TSamp;

  /* Sum: '<Root>/Sum' incorporates:
   *  Constant: '<Root>/Plane limit1'
   */
  rtb_Sum[2] = pid_ctrl_P.Planelimit1_Value[2] - rtb_Sum2[2];

  /* Gain: '<Root>/Gain2' */
  rtb_Sum1[2] = pid_ctrl_P.Gain2_Gain * rtb_Sum[2];

  /* SampleTimeMath: '<S1>/TSamp'
   *
   * About '<S1>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_TSamp = rtb_Sum1[2] * pid_ctrl_P.TSamp_WtEt;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Gravity compensation'
   *  DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
   *  Gain: '<Root>/Gain'
   *  Sum: '<Root>/Sum3'
   *  Sum: '<S1>/Diff'
   *  UnitDelay: '<S1>/UD'
   */
  rtb_Sum1[2] = ((pid_ctrl_P.Gain_Gain * rtb_Sum[2] +
                  pid_ctrl_DW.DiscreteTimeIntegrator_DSTATE[2]) + (rtb_TSamp -
    pid_ctrl_DW.UD_DSTATE[2])) + pid_ctrl_P.Gravitycompensation_Value[2];

  /* BusAssignment: '<S2>/Bus Assignment' incorporates:
   *  Constant: '<S5>/Constant'
   */
  rtb_BusAssignment = pid_ctrl_P.Constant_Value_j;
  rtb_BusAssignment.Force.X = rtb_Sum1[0];
  rtb_BusAssignment.Force.Y = rtb_Sum1[1];
  rtb_BusAssignment.Force.Z = rtb_Sum1[2];

  /* Outputs for Atomic SubSystem: '<S2>/Publish' */
  /* MATLABSystem: '<S6>/SinkBlock' */
  Pub_pid_ctrl_22.publish(&rtb_BusAssignment);

  /* End of Outputs for SubSystem: '<S2>/Publish' */
  /* Step: '<Root>/Step' */
  currentTime = pid_ctrl_M->Timing.taskTime0;
  if (currentTime < pid_ctrl_P.Ts) {
    currentTime = pid_ctrl_P.Step_Y0;
  } else {
    currentTime = pid_ctrl_P.Step_YFinal;
  }

  /* End of Step: '<Root>/Step' */

  /* Outputs for Enabled SubSystem: '<Root>/Reset World' incorporates:
   *  EnablePort: '<S4>/Enable'
   */
  if (currentTime > 0.0) {
    if (!pid_ctrl_DW.ResetWorld_MODE) {
      pid_ctrl_DW.ResetWorld_MODE = true;
    }

    /* Outputs for Atomic SubSystem: '<S4>/Call Service' */
    /* MATLABSystem: '<S10>/ServiceCaller' incorporates:
     *  Constant: '<S9>/Constant'
     */
    isCreated = ServCall_pid_ctrl_43.getIsCreated();
    if (!isCreated) {
      for (i = 0; i < 20; i++) {
        tmp_0[i] = tmp[i];
      }

      b_varargout_2_0 = ServCall_pid_ctrl_43.createServiceCaller(tmp_0, false,
        5.0);
      if (b_varargout_2_0 != SLSuccess) {
      } else {
        ServCall_pid_ctrl_43.call(&pid_ctrl_P.Constant_Value_a, &b_varargout_1);
      }
    } else {
      ServCall_pid_ctrl_43.call(&pid_ctrl_P.Constant_Value_a, &b_varargout_1);
    }

    /* End of MATLABSystem: '<S10>/ServiceCaller' */
    /* End of Outputs for SubSystem: '<S4>/Call Service' */
  } else {
    if (pid_ctrl_DW.ResetWorld_MODE) {
      pid_ctrl_DW.ResetWorld_MODE = false;
    }
  }

  /* End of Outputs for SubSystem: '<Root>/Reset World' */

  /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' incorporates:
   *  Gain: '<Root>/Gain1'
   */
  pid_ctrl_DW.DiscreteTimeIntegrator_DSTATE[0] += pid_ctrl_P.Gain1_Gain *
    rtb_Sum[0] * pid_ctrl_P.DiscreteTimeIntegrator_gainval;

  /* Update for UnitDelay: '<S1>/UD' */
  pid_ctrl_DW.UD_DSTATE[0] = rtb_TSamp_idx_0;

  /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' incorporates:
   *  Gain: '<Root>/Gain1'
   */
  pid_ctrl_DW.DiscreteTimeIntegrator_DSTATE[1] += pid_ctrl_P.Gain1_Gain *
    rtb_Sum[1] * pid_ctrl_P.DiscreteTimeIntegrator_gainval;

  /* Update for UnitDelay: '<S1>/UD' */
  pid_ctrl_DW.UD_DSTATE[1] = rtb_TSamp_idx_1;

  /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' incorporates:
   *  Gain: '<Root>/Gain1'
   */
  pid_ctrl_DW.DiscreteTimeIntegrator_DSTATE[2] += pid_ctrl_P.Gain1_Gain *
    rtb_Sum[2] * pid_ctrl_P.DiscreteTimeIntegrator_gainval;

  /* Update for UnitDelay: '<S1>/UD' */
  pid_ctrl_DW.UD_DSTATE[2] = rtb_TSamp;

  /* Matfile logging */
  rt_UpdateTXYLogVars(pid_ctrl_M->rtwLogInfo, (&pid_ctrl_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.01s, 0.0s] */
    if ((rtmGetTFinal(pid_ctrl_M)!=-1) &&
        !((rtmGetTFinal(pid_ctrl_M)-pid_ctrl_M->Timing.taskTime0) >
          pid_ctrl_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(pid_ctrl_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++pid_ctrl_M->Timing.clockTick0)) {
    ++pid_ctrl_M->Timing.clockTickH0;
  }

  pid_ctrl_M->Timing.taskTime0 = pid_ctrl_M->Timing.clockTick0 *
    pid_ctrl_M->Timing.stepSize0 + pid_ctrl_M->Timing.clockTickH0 *
    pid_ctrl_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void pid_ctrl_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)pid_ctrl_M, 0,
                sizeof(RT_MODEL_pid_ctrl_T));
  rtmSetTFinal(pid_ctrl_M, -1);
  pid_ctrl_M->Timing.stepSize0 = 0.01;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    pid_ctrl_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(pid_ctrl_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(pid_ctrl_M->rtwLogInfo, (NULL));
    rtliSetLogT(pid_ctrl_M->rtwLogInfo, "tout");
    rtliSetLogX(pid_ctrl_M->rtwLogInfo, "");
    rtliSetLogXFinal(pid_ctrl_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(pid_ctrl_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(pid_ctrl_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(pid_ctrl_M->rtwLogInfo, 0);
    rtliSetLogDecimation(pid_ctrl_M->rtwLogInfo, 1);
    rtliSetLogY(pid_ctrl_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(pid_ctrl_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(pid_ctrl_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &pid_ctrl_B), 0,
                sizeof(B_pid_ctrl_T));

  /* states (dwork) */
  (void) memset((void *)&pid_ctrl_DW, 0,
                sizeof(DW_pid_ctrl_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(pid_ctrl_M->rtwLogInfo, 0.0, rtmGetTFinal
    (pid_ctrl_M), pid_ctrl_M->Timing.stepSize0, (&rtmGetErrorStatus(pid_ctrl_M)));

  {
    static const char_T tmp[29] = { '/', 'f', 'o', 'r', 'c', 'e', '_', 'c', 'o',
      'n', 't', 'r', 'o', 'l', '/', 'c', 'o', 'm', 'm', 'a', 'n', 'd', '/', 'w',
      'r', 'e', 'n', 'c', 'h' };

    static const char_T tmp_0[23] = { '/', 'f', 'o', 'r', 'c', 'e', '_', 'c',
      'o', 'n', 't', 'r', 'o', 'l', '/', 'o', 'd', 'o', 'm', 'e', 't', 'r', 'y'
    };

    char_T tmp_1[30];
    char_T tmp_2[24];
    int32_T i;

    /* Start for Atomic SubSystem: '<S3>/Subscribe' */
    /* Start for MATLABSystem: '<S7>/SourceBlock' */
    pid_ctrl_DW.obj_n.matlabCodegenIsDeleted = true;
    pid_ctrl_DW.obj_n.isInitialized = 0;
    pid_ctrl_DW.obj_n.matlabCodegenIsDeleted = false;
    pid_ctrl_DW.objisempty_g = true;
    pid_ctrl_DW.obj_n.isSetupComplete = false;
    pid_ctrl_DW.obj_n.isInitialized = 1;
    for (i = 0; i < 23; i++) {
      tmp_2[i] = tmp_0[i];
    }

    tmp_2[23] = '\x00';
    Sub_pid_ctrl_1.createSubscriber(tmp_2, 1);
    pid_ctrl_DW.obj_n.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S7>/SourceBlock' */
    /* End of Start for SubSystem: '<S3>/Subscribe' */

    /* Start for Atomic SubSystem: '<S2>/Publish' */
    /* Start for MATLABSystem: '<S6>/SinkBlock' */
    pid_ctrl_DW.obj.matlabCodegenIsDeleted = true;
    pid_ctrl_DW.obj.isInitialized = 0;
    pid_ctrl_DW.obj.matlabCodegenIsDeleted = false;
    pid_ctrl_DW.objisempty_e = true;
    pid_ctrl_DW.obj.isSetupComplete = false;
    pid_ctrl_DW.obj.isInitialized = 1;
    for (i = 0; i < 29; i++) {
      tmp_1[i] = tmp[i];
    }

    tmp_1[29] = '\x00';
    Pub_pid_ctrl_22.createPublisher(tmp_1, 1);
    pid_ctrl_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S6>/SinkBlock' */
    /* End of Start for SubSystem: '<S2>/Publish' */
    /* Start for Enabled SubSystem: '<Root>/Reset World' */
    /* Start for Atomic SubSystem: '<S4>/Call Service' */
    /* Start for MATLABSystem: '<S10>/ServiceCaller' */
    pid_ctrl_DW.obj_m.matlabCodegenIsDeleted = true;
    pid_ctrl_DW.obj_m.isInitialized = 0;
    pid_ctrl_DW.obj_m.matlabCodegenIsDeleted = false;
    pid_ctrl_DW.objisempty = true;
    pid_ctrl_DW.obj_m.isSetupComplete = false;
    pid_ctrl_DW.obj_m.isInitialized = 1;
    pid_ctrl_DW.obj_m.isSetupComplete = true;

    /* End of Start for SubSystem: '<S4>/Call Service' */
    /* End of Start for SubSystem: '<Root>/Reset World' */

    /* Start for MATLABSystem: '<Root>/Simulation Rate Control' */
    pid_ctrl_DW.obj_e.isInitialized = 0;
    pid_ctrl_DW.objisempty_h = true;
    pid_ctrl_DW.obj_e.isInitialized = 1;
  }

  /* InitializeConditions for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  pid_ctrl_DW.DiscreteTimeIntegrator_DSTATE[0] =
    pid_ctrl_P.DiscreteTimeIntegrator_IC;

  /* InitializeConditions for UnitDelay: '<S1>/UD' */
  pid_ctrl_DW.UD_DSTATE[0] = pid_ctrl_P.DiscreteDerivative_ICPrevScaled;

  /* InitializeConditions for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  pid_ctrl_DW.DiscreteTimeIntegrator_DSTATE[1] =
    pid_ctrl_P.DiscreteTimeIntegrator_IC;

  /* InitializeConditions for UnitDelay: '<S1>/UD' */
  pid_ctrl_DW.UD_DSTATE[1] = pid_ctrl_P.DiscreteDerivative_ICPrevScaled;

  /* InitializeConditions for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  pid_ctrl_DW.DiscreteTimeIntegrator_DSTATE[2] =
    pid_ctrl_P.DiscreteTimeIntegrator_IC;

  /* InitializeConditions for UnitDelay: '<S1>/UD' */
  pid_ctrl_DW.UD_DSTATE[2] = pid_ctrl_P.DiscreteDerivative_ICPrevScaled;

  /* SystemInitialize for Atomic SubSystem: '<S3>/Subscribe' */
  /* SystemInitialize for Enabled SubSystem: '<S7>/Enabled Subsystem' */
  /* SystemInitialize for Outport: '<S8>/Out1' */
  pid_ctrl_B.In1 = pid_ctrl_P.Out1_Y0;

  /* End of SystemInitialize for SubSystem: '<S7>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<S3>/Subscribe' */
}

/* Model terminate function */
void pid_ctrl_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<S3>/Subscribe' */
  /* Terminate for MATLABSystem: '<S7>/SourceBlock' */
  matlabCodegenHandle_matlabCod_k(&pid_ctrl_DW.obj_n);

  /* End of Terminate for SubSystem: '<S3>/Subscribe' */

  /* Terminate for Atomic SubSystem: '<S2>/Publish' */
  /* Terminate for MATLABSystem: '<S6>/SinkBlock' */
  matlabCodegenHandle_matlabCodeg(&pid_ctrl_DW.obj);

  /* End of Terminate for SubSystem: '<S2>/Publish' */

  /* Terminate for Enabled SubSystem: '<Root>/Reset World' */
  /* Terminate for Atomic SubSystem: '<S4>/Call Service' */
  /* Terminate for MATLABSystem: '<S10>/ServiceCaller' */
  matlabCodegenHandle_matlabCo_k1(&pid_ctrl_DW.obj_m);

  /* End of Terminate for SubSystem: '<S4>/Call Service' */
  /* End of Terminate for SubSystem: '<Root>/Reset World' */
}
