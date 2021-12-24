/*
 * File: pathRadius_data.c
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

#include "pathRadius.h"
#include "pathRadius_private.h"

/* Invariant block signals (default storage) */
const ConstB_pathRadius_T pathRadius_ConstB = {
  0.0,                                 /* '<S6>/Constant' */
  0.0                                  /* '<S13>/Constant' */
};

/* Constant parameters (default storage) */
const ConstP_pathRadius_T pathRadius_ConstP = {
  /* Expression: [100 90 80 70 60 50 40 30 20 10 0]
   * Referenced by: '<S2>/1-D Lookup Table1'
   */
  { 100.0, 90.0, 80.0, 70.0, 60.0, 50.0, 40.0, 30.0, 20.0, 10.0, 0.0 },

  /* Expression: [0 0.5 1 1.5 2 2.5 5 10 15 20 25]
   * Referenced by: '<S2>/1-D Lookup Table1'
   */
  { 0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 5.0, 10.0, 15.0, 20.0, 25.0 }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
