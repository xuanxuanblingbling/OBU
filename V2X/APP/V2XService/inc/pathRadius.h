/*
 * File: pathRadius.h
 *
 * Code generated for Simulink model 'pathRadius'.
 *
 * Model version                  : 1.38
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Fri Aug  7 11:00:41 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_pathRadius_h_
#define RTW_HEADER_pathRadius_h_
#include <math.h>
#ifndef pathRadius_COMMON_INCLUDES_
# define pathRadius_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* pathRadius_COMMON_INCLUDES_ */

#include "pathRadius_types.h"
//#include "prot_element.h"
#include "wjv4_uper_De.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Probe[2];                     /* '<S7>/Probe' */
  real_T Probe_k[2];                   /* '<S14>/Probe' */
} B_pathRadius_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S11>/Integrator' */
  real_T Integrator_DSTATE_a;          /* '<S12>/Integrator' */
  real_T Integrator_DSTATE_n;          /* '<S19>/Integrator' */
  real_T Integrator_DSTATE_ae;         /* '<S18>/Integrator' */
  int8_T Integrator_PrevResetState;    /* '<S11>/Integrator' */
  int8_T Integrator_PrevResetState_b;  /* '<S12>/Integrator' */
  int8_T Integrator_PrevResetState_l;  /* '<S19>/Integrator' */
  int8_T Integrator_PrevResetState_f;  /* '<S18>/Integrator' */
  uint8_T Integrator_IC_LOADING;       /* '<S12>/Integrator' */
  uint8_T Integrator_IC_LOADING_a;     /* '<S19>/Integrator' */
} DW_pathRadius_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Constant;               /* '<S6>/Constant' */
  const real_T Constant_h;             /* '<S13>/Constant' */
} ConstB_pathRadius_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: [100 90 80 70 60 50 40 30 20 10 0]
   * Referenced by: '<S2>/1-D Lookup Table1'
   */
  real_T uDLookupTable1_tableData[11];

  /* Expression: [0 0.5 1 1.5 2 2.5 5 10 15 20 25]
   * Referenced by: '<S2>/1-D Lookup Table1'
   */
  real_T uDLookupTable1_bp01Data[11];
} ConstP_pathRadius_T;

///* External inputs (root inport signals with default storage) */
//typedef struct {
//  real_T yawrate;                      /* '<Root>/yawrate' */
//  real_T speed;                        /* '<Root>/speed ' */
//} ExtU_pathRadius_T;

///* External outputs (root outports fed by signals with default storage) */
//typedef struct {
//  real_T FilteredRadiusM;              /* '<Root>/FilteredRadiusM ' */
//  real_T HVPP_Confidence;              /* '<Root>/HVPP_Confidence' */
//} ExtY_pathRadius_T;

typedef struct {
  WJV4_INT_YawRate  yawrate; /* '<Root>/yawrate' */
  WJV4_INT_Speed   speed;     /* '<Root>/speed ' */
} ExtU_pathRadius_T;

typedef struct {
  WJV4_INT_RadiusOfCurvation FilteredRadiusM; /* '<Root>/FilteredRadiusM ' */
  WJV4_INT_Confidence HVPP_Confidence;        /* '<Root>/HVPP_Confidence' */
} ExtY_pathRadius_T;


/* Real-time Model Data Structure */
struct tag_RTM_pathRadius_T {
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_pathRadius_T pathRadius_B;

/* Block states (default storage) */
extern DW_pathRadius_T pathRadius_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_pathRadius_T pathRadius_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_pathRadius_T pathRadius_Y;

extern const ConstB_pathRadius_T pathRadius_ConstB;/* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP_pathRadius_T pathRadius_ConstP;

/* Model entry point functions */
extern void pathRadius_initialize(void);
//extern void pathRadius_step(void);
extern ExtY_pathRadius_T pathRadius_step(ExtU_pathRadius_T pathRadius_U);
extern void pathRadius_terminate(void);

/* Real-time Model object */
extern RT_MODEL_pathRadius_T *const pathRadius_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S11>/Saturation' : Eliminated Saturate block
 * Block '<S12>/Saturation' : Eliminated Saturate block
 * Block '<S18>/Saturation' : Eliminated Saturate block
 * Block '<S19>/Saturation' : Eliminated Saturate block
 */

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
 * '<Root>' : 'pathRadius'
 * '<S1>'   : 'pathRadius/Subsystem'
 * '<S2>'   : 'pathRadius/Subsystem1'
 * '<S3>'   : 'pathRadius/Subsystem/Compare To Constant'
 * '<S4>'   : 'pathRadius/Subsystem/Compare To Constant1'
 * '<S5>'   : 'pathRadius/Subsystem/Subsystem'
 * '<S6>'   : 'pathRadius/Subsystem/Subsystem/Second-Order Low-Pass Filter (Discrete or Continuous)'
 * '<S7>'   : 'pathRadius/Subsystem/Subsystem/Second-Order Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant'
 * '<S8>'   : 'pathRadius/Subsystem/Subsystem/Second-Order Low-Pass Filter (Discrete or Continuous)/x1'
 * '<S9>'   : 'pathRadius/Subsystem/Subsystem/Second-Order Low-Pass Filter (Discrete or Continuous)/x2'
 * '<S10>'  : 'pathRadius/Subsystem/Subsystem/Second-Order Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant/MATLAB Function'
 * '<S11>'  : 'pathRadius/Subsystem/Subsystem/Second-Order Low-Pass Filter (Discrete or Continuous)/x1/Discrete'
 * '<S12>'  : 'pathRadius/Subsystem/Subsystem/Second-Order Low-Pass Filter (Discrete or Continuous)/x2/Discrete'
 * '<S13>'  : 'pathRadius/Subsystem1/Second-Order Low-Pass Filter (Discrete or Continuous)'
 * '<S14>'  : 'pathRadius/Subsystem1/Second-Order Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant'
 * '<S15>'  : 'pathRadius/Subsystem1/Second-Order Low-Pass Filter (Discrete or Continuous)/x1'
 * '<S16>'  : 'pathRadius/Subsystem1/Second-Order Low-Pass Filter (Discrete or Continuous)/x2'
 * '<S17>'  : 'pathRadius/Subsystem1/Second-Order Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant/MATLAB Function'
 * '<S18>'  : 'pathRadius/Subsystem1/Second-Order Low-Pass Filter (Discrete or Continuous)/x1/Discrete'
 * '<S19>'  : 'pathRadius/Subsystem1/Second-Order Low-Pass Filter (Discrete or Continuous)/x2/Discrete'
 */
#endif                                 /* RTW_HEADER_pathRadius_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
