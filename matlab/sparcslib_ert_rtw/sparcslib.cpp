//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: sparcslib.cpp
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
#include "sparcslib.h"
#include "sparcslib_private.h"

// Block signals (default storage)
B_sparcslib_T sparcslib_B;

// Block states (default storage)
DW_sparcslib_T sparcslib_DW;

// Real-time model
RT_MODEL_sparcslib_T sparcslib_M_;
RT_MODEL_sparcslib_T *const sparcslib_M = &sparcslib_M_;

// Forward declaration for local functions
static void sparcslib_matlabCodegenHandle_matlabCodegenDestructor_k
  (robotics_slros_internal_block_Subscriber_sparcslib_T *obj);
static void sparcslib_matlabCodegenHandle_matlabCodegenDestructor
  (robotics_slros_internal_block_Publisher_sparcslib_T *obj);
static void sparcslib_matlabCodegenHandle_matlabCodegenDestructor_k
  (robotics_slros_internal_block_Subscriber_sparcslib_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
  }
}

static void sparcslib_matlabCodegenHandle_matlabCodegenDestructor
  (robotics_slros_internal_block_Publisher_sparcslib_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
  }
}

// Model step function
void sparcslib_step(void)
{
  boolean_T b_varargout_1;
  real_T rtb_TSamp;
  real_T rtb_Sum_idx_0;
  real_T rtb_Sum_idx_1;
  real_T rtb_Sum_idx_2;
  real_T rtb_TSamp_idx_0;
  real_T rtb_TSamp_idx_1;

  // Outputs for Atomic SubSystem: '<S3>/Subscribe'
  // MATLABSystem: '<S6>/SourceBlock' incorporates:
  //   Inport: '<S7>/In1'

  b_varargout_1 = Sub_sparcslib_1.getLatestMessage(&sparcslib_B.b_varargout_2);

  // Outputs for Enabled SubSystem: '<S6>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S7>/Enable'

  if (b_varargout_1) {
    sparcslib_B.In1 = sparcslib_B.b_varargout_2;
  }

  // End of MATLABSystem: '<S6>/SourceBlock'
  // End of Outputs for SubSystem: '<S6>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<S3>/Subscribe'

  // Sum: '<Root>/Sum' incorporates:
  //   Constant: '<Root>/Plane limit'
  //   Constant: '<Root>/Plane limit1'
  //   Sum: '<Root>/Sum2'

  rtb_Sum_idx_0 = sparcslib_P.Planelimit1_Value[0] -
    (sparcslib_B.In1.Pose.Pose.Position.X - sparcslib_P.Planelimit_Value[0]);
  rtb_Sum_idx_1 = sparcslib_P.Planelimit1_Value[1] -
    (sparcslib_B.In1.Pose.Pose.Position.Y - sparcslib_P.Planelimit_Value[1]);
  rtb_Sum_idx_2 = sparcslib_P.Planelimit1_Value[2] -
    (sparcslib_B.In1.Pose.Pose.Position.Z - sparcslib_P.Planelimit_Value[2]);

  // SampleTimeMath: '<S1>/TSamp' incorporates:
  //   Gain: '<Root>/Gain2'
  //
  //  About '<S1>/TSamp':
  //   y = u * K where K = 1 / ( w * Ts )

  rtb_TSamp = sparcslib_P.Gain2_Gain * rtb_Sum_idx_0 * sparcslib_P.TSamp_WtEt;

  // Sum: '<Root>/Sum1' incorporates:
  //   Constant: '<Root>/Gravity compensation'
  //   DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
  //   Gain: '<Root>/Gain'
  //   Gain: '<Root>/Gain2'
  //   Sum: '<Root>/Sum3'
  //   Sum: '<S1>/Diff'
  //   UnitDelay: '<S1>/UD'
  //
  //  Block description for '<S1>/Diff':
  //
  //   Add in CPU
  //
  //  Block description for '<S1>/UD':
  //
  //   Store in Global RAM

  sparcslib_DW.UD_DSTATE[0] = ((sparcslib_P.Gain_Gain * rtb_Sum_idx_0 +
    sparcslib_DW.DiscreteTimeIntegrator_DSTATE[0]) + (rtb_TSamp -
    sparcslib_DW.UD_DSTATE[0])) + sparcslib_P.Gravitycompensation_Value[0];

  // SampleTimeMath: '<S1>/TSamp' incorporates:
  //   Gain: '<Root>/Gain2'
  //
  //  About '<S1>/TSamp':
  //   y = u * K where K = 1 / ( w * Ts )

  rtb_TSamp_idx_0 = rtb_TSamp;
  rtb_TSamp = sparcslib_P.Gain2_Gain * rtb_Sum_idx_1 * sparcslib_P.TSamp_WtEt;

  // Sum: '<Root>/Sum1' incorporates:
  //   Constant: '<Root>/Gravity compensation'
  //   DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
  //   Gain: '<Root>/Gain'
  //   Gain: '<Root>/Gain2'
  //   Sum: '<Root>/Sum3'
  //   Sum: '<S1>/Diff'
  //   UnitDelay: '<S1>/UD'
  //
  //  Block description for '<S1>/Diff':
  //
  //   Add in CPU
  //
  //  Block description for '<S1>/UD':
  //
  //   Store in Global RAM

  sparcslib_DW.UD_DSTATE[1] = ((sparcslib_P.Gain_Gain * rtb_Sum_idx_1 +
    sparcslib_DW.DiscreteTimeIntegrator_DSTATE[1]) + (rtb_TSamp -
    sparcslib_DW.UD_DSTATE[1])) + sparcslib_P.Gravitycompensation_Value[1];

  // SampleTimeMath: '<S1>/TSamp' incorporates:
  //   Gain: '<Root>/Gain2'
  //
  //  About '<S1>/TSamp':
  //   y = u * K where K = 1 / ( w * Ts )

  rtb_TSamp_idx_1 = rtb_TSamp;
  rtb_TSamp = sparcslib_P.Gain2_Gain * rtb_Sum_idx_2 * sparcslib_P.TSamp_WtEt;

  // Sum: '<Root>/Sum1' incorporates:
  //   Constant: '<Root>/Gravity compensation'
  //   DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
  //   Gain: '<Root>/Gain'
  //   Gain: '<Root>/Gain2'
  //   Sum: '<Root>/Sum3'
  //   Sum: '<S1>/Diff'
  //   UnitDelay: '<S1>/UD'
  //
  //  Block description for '<S1>/Diff':
  //
  //   Add in CPU
  //
  //  Block description for '<S1>/UD':
  //
  //   Store in Global RAM

  sparcslib_DW.UD_DSTATE[2] = ((sparcslib_P.Gain_Gain * rtb_Sum_idx_2 +
    sparcslib_DW.DiscreteTimeIntegrator_DSTATE[2]) + (rtb_TSamp -
    sparcslib_DW.UD_DSTATE[2])) + sparcslib_P.Gravitycompensation_Value[2];

  // BusAssignment: '<S2>/Bus Assignment' incorporates:
  //   Constant: '<S4>/Constant'

  sparcslib_B.BusAssignment = sparcslib_P.Constant_Value_j;
  sparcslib_B.BusAssignment.Force.X = sparcslib_DW.UD_DSTATE[0];
  sparcslib_B.BusAssignment.Force.Y = sparcslib_DW.UD_DSTATE[1];
  sparcslib_B.BusAssignment.Force.Z = sparcslib_DW.UD_DSTATE[2];

  // Outputs for Atomic SubSystem: '<S2>/Publish'
  // MATLABSystem: '<S5>/SinkBlock'
  Pub_sparcslib_22.publish(&sparcslib_B.BusAssignment);

  // End of Outputs for SubSystem: '<S2>/Publish'

  // Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' incorporates:
  //   Gain: '<Root>/Gain1'

  sparcslib_DW.DiscreteTimeIntegrator_DSTATE[0] += sparcslib_P.Gain1_Gain *
    rtb_Sum_idx_0 * sparcslib_P.DiscreteTimeIntegrator_gainval;

  // Update for UnitDelay: '<S1>/UD'
  //
  //  Block description for '<S1>/UD':
  //
  //   Store in Global RAM

  sparcslib_DW.UD_DSTATE[0] = rtb_TSamp_idx_0;

  // Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' incorporates:
  //   Gain: '<Root>/Gain1'

  sparcslib_DW.DiscreteTimeIntegrator_DSTATE[1] += sparcslib_P.Gain1_Gain *
    rtb_Sum_idx_1 * sparcslib_P.DiscreteTimeIntegrator_gainval;

  // Update for UnitDelay: '<S1>/UD'
  //
  //  Block description for '<S1>/UD':
  //
  //   Store in Global RAM

  sparcslib_DW.UD_DSTATE[1] = rtb_TSamp_idx_1;

  // Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' incorporates:
  //   Gain: '<Root>/Gain1'

  sparcslib_DW.DiscreteTimeIntegrator_DSTATE[2] += sparcslib_P.Gain1_Gain *
    rtb_Sum_idx_2 * sparcslib_P.DiscreteTimeIntegrator_gainval;

  // Update for UnitDelay: '<S1>/UD'
  //
  //  Block description for '<S1>/UD':
  //
  //   Store in Global RAM

  sparcslib_DW.UD_DSTATE[2] = rtb_TSamp;
}

// Model initialize function
void sparcslib_initialize(void)
{
  // Registration code

  // initialize error status
  rtmSetErrorStatus(sparcslib_M, (NULL));

  // block I/O
  (void) memset(((void *) &sparcslib_B), 0,
                sizeof(B_sparcslib_T));

  // states (dwork)
  (void) memset((void *)&sparcslib_DW, 0,
                sizeof(DW_sparcslib_T));

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

    // Start for Atomic SubSystem: '<S3>/Subscribe'
    // Start for MATLABSystem: '<S6>/SourceBlock'
    sparcslib_DW.obj_n.matlabCodegenIsDeleted = true;
    sparcslib_DW.obj_n.isInitialized = 0;
    sparcslib_DW.obj_n.matlabCodegenIsDeleted = false;
    sparcslib_DW.obj_n.isSetupComplete = false;
    sparcslib_DW.obj_n.isInitialized = 1;
    for (i = 0; i < 23; i++) {
      tmp_2[i] = tmp_0[i];
    }

    tmp_2[23] = '\x00';
    Sub_sparcslib_1.createSubscriber(tmp_2, 1);
    sparcslib_DW.obj_n.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S6>/SourceBlock'
    // End of Start for SubSystem: '<S3>/Subscribe'

    // Start for Atomic SubSystem: '<S2>/Publish'
    // Start for MATLABSystem: '<S5>/SinkBlock'
    sparcslib_DW.obj.matlabCodegenIsDeleted = true;
    sparcslib_DW.obj.isInitialized = 0;
    sparcslib_DW.obj.matlabCodegenIsDeleted = false;
    sparcslib_DW.obj.isSetupComplete = false;
    sparcslib_DW.obj.isInitialized = 1;
    for (i = 0; i < 29; i++) {
      tmp_1[i] = tmp[i];
    }

    tmp_1[29] = '\x00';
    Pub_sparcslib_22.createPublisher(tmp_1, 1);
    sparcslib_DW.obj.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S5>/SinkBlock'
    // End of Start for SubSystem: '<S2>/Publish'

    // InitializeConditions for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' 
    sparcslib_DW.DiscreteTimeIntegrator_DSTATE[0] =
      sparcslib_P.DiscreteTimeIntegrator_IC;

    // InitializeConditions for UnitDelay: '<S1>/UD'
    //
    //  Block description for '<S1>/UD':
    //
    //   Store in Global RAM

    sparcslib_DW.UD_DSTATE[0] = sparcslib_P.DiscreteDerivative_ICPrevScaledInput;

    // InitializeConditions for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' 
    sparcslib_DW.DiscreteTimeIntegrator_DSTATE[1] =
      sparcslib_P.DiscreteTimeIntegrator_IC;

    // InitializeConditions for UnitDelay: '<S1>/UD'
    //
    //  Block description for '<S1>/UD':
    //
    //   Store in Global RAM

    sparcslib_DW.UD_DSTATE[1] = sparcslib_P.DiscreteDerivative_ICPrevScaledInput;

    // InitializeConditions for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' 
    sparcslib_DW.DiscreteTimeIntegrator_DSTATE[2] =
      sparcslib_P.DiscreteTimeIntegrator_IC;

    // InitializeConditions for UnitDelay: '<S1>/UD'
    //
    //  Block description for '<S1>/UD':
    //
    //   Store in Global RAM

    sparcslib_DW.UD_DSTATE[2] = sparcslib_P.DiscreteDerivative_ICPrevScaledInput;

    // SystemInitialize for Atomic SubSystem: '<S3>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S6>/Enabled Subsystem'
    // SystemInitialize for Outport: '<S7>/Out1'
    sparcslib_B.In1 = sparcslib_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S6>/Enabled Subsystem'
    // End of SystemInitialize for SubSystem: '<S3>/Subscribe'
  }
}

// Model terminate function
void sparcslib_terminate(void)
{
  // Terminate for Atomic SubSystem: '<S3>/Subscribe'
  // Terminate for MATLABSystem: '<S6>/SourceBlock'
  sparcslib_matlabCodegenHandle_matlabCodegenDestructor_k(&sparcslib_DW.obj_n);

  // End of Terminate for SubSystem: '<S3>/Subscribe'

  // Terminate for Atomic SubSystem: '<S2>/Publish'
  // Terminate for MATLABSystem: '<S5>/SinkBlock'
  sparcslib_matlabCodegenHandle_matlabCodegenDestructor(&sparcslib_DW.obj);

  // End of Terminate for SubSystem: '<S2>/Publish'
}

//
// File trailer for generated code.
//
// [EOF]
//
