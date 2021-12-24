/*
 * File: pathRadius_private.h
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

#ifndef RTW_HEADER_pathRadius_private_h_
#define RTW_HEADER_pathRadius_private_h_
#include "rtwtypes.h"
#include "pathRadius.h"

extern real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex);
extern void pathRadius_MATLABFunction(real_T rtu_Ts, real_T *rty_forward_gain,
  real_T *rty_reset, real_T rtp_A1, real_T rtp_A2);

#endif                                 /* RTW_HEADER_pathRadius_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
