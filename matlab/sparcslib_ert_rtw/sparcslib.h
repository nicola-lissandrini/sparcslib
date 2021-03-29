//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: sparcslib.h
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
#ifndef RTW_HEADER_sparcslib_h_
#define RTW_HEADER_sparcslib_h_
#include <stddef.h>
#include <string.h>
#ifndef sparcslib_COMMON_INCLUDES_
# define sparcslib_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "slros_initialize.h"
#endif                                 // sparcslib_COMMON_INCLUDES_

#include "sparcslib_types.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

// Block signals (default storage)
typedef struct {
  SL_Bus_sparcslib_nav_msgs_Odometry In1;// '<S7>/In1'
  SL_Bus_sparcslib_nav_msgs_Odometry b_varargout_2;
  SL_Bus_sparcslib_geometry_msgs_Wrench BusAssignment;// '<S2>/Bus Assignment'
} B_sparcslib_T;

// Block states (default storage) for system '<Root>'
typedef struct {
  robotics_slros_internal_block_Publisher_sparcslib_T obj;// '<S5>/SinkBlock'
  robotics_slros_internal_block_Subscriber_sparcslib_T obj_n;// '<S6>/SourceBlock' 
  real_T DiscreteTimeIntegrator_DSTATE[3];// '<Root>/Discrete-Time Integrator'
  real_T UD_DSTATE[3];                 // '<S1>/UD'
} DW_sparcslib_T;

// Parameters (default storage)
struct P_sparcslib_T_ {
  real_T DiscreteDerivative_ICPrevScaledInput;
                         // Mask Parameter: DiscreteDerivative_ICPrevScaledInput
                            //  Referenced by: '<S1>/UD'

  SL_Bus_sparcslib_nav_msgs_Odometry Out1_Y0;// Computed Parameter: Out1_Y0
                                                //  Referenced by: '<S7>/Out1'

  SL_Bus_sparcslib_nav_msgs_Odometry Constant_Value;// Computed Parameter: Constant_Value
                                                       //  Referenced by: '<S6>/Constant'

  SL_Bus_sparcslib_geometry_msgs_Wrench Constant_Value_j;// Computed Parameter: Constant_Value_j
                                                            //  Referenced by: '<S4>/Constant'

  real_T Planelimit_Value[3];          // Expression: [0, 0, 0.1]
                                          //  Referenced by: '<Root>/Plane limit'

  real_T Planelimit1_Value[3];         // Expression: [0, 0, 1]
                                          //  Referenced by: '<Root>/Plane limit1'

  real_T Gain_Gain;                    // Expression: 10
                                          //  Referenced by: '<Root>/Gain'

  real_T DiscreteTimeIntegrator_gainval;
                           // Computed Parameter: DiscreteTimeIntegrator_gainval
                              //  Referenced by: '<Root>/Discrete-Time Integrator'

  real_T DiscreteTimeIntegrator_IC;    // Expression: 0
                                          //  Referenced by: '<Root>/Discrete-Time Integrator'

  real_T Gain2_Gain;                   // Expression: 10
                                          //  Referenced by: '<Root>/Gain2'

  real_T TSamp_WtEt;                   // Computed Parameter: TSamp_WtEt
                                          //  Referenced by: '<S1>/TSamp'

  real_T Gravitycompensation_Value[3]; // Expression: [0, 0, mass*g]
                                          //  Referenced by: '<Root>/Gravity compensation'

  real_T Gain1_Gain;                   // Expression: 0.1
                                          //  Referenced by: '<Root>/Gain1'

};

// Real-time Model Data Structure
struct tag_RTM_sparcslib_T {
  const char_T *errorStatus;
};

// Block parameters (default storage)
#ifdef __cplusplus

extern "C" {

#endif

  extern P_sparcslib_T sparcslib_P;

#ifdef __cplusplus

}
#endif

// Block signals (default storage)
extern B_sparcslib_T sparcslib_B;

// Block states (default storage)
extern DW_sparcslib_T sparcslib_DW;

#ifdef __cplusplus

extern "C" {

#endif

  // Model entry point functions
  extern void sparcslib_initialize(void);
  extern void sparcslib_step(void);
  extern void sparcslib_terminate(void);

#ifdef __cplusplus

}
#endif

// Real-time Model object
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_sparcslib_T *const sparcslib_M;

#ifdef __cplusplus

}
#endif

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S1>/Data Type Duplicate' : Unused code path elimination
//  Block '<Root>/Scope' : Unused code path elimination
//  Block '<Root>/Scope1' : Unused code path elimination
//  Block '<Root>/Scope2' : Unused code path elimination


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'sparcslib'
//  '<S1>'   : 'sparcslib/Discrete Derivative'
//  '<S2>'   : 'sparcslib/ROS Command out'
//  '<S3>'   : 'sparcslib/ROS state IN'
//  '<S4>'   : 'sparcslib/ROS Command out/Blank Message'
//  '<S5>'   : 'sparcslib/ROS Command out/Publish'
//  '<S6>'   : 'sparcslib/ROS state IN/Subscribe'
//  '<S7>'   : 'sparcslib/ROS state IN/Subscribe/Enabled Subsystem'

#endif                                 // RTW_HEADER_sparcslib_h_

//
// File trailer for generated code.
//
// [EOF]
//
