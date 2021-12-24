/*
 * File: pathRadius.c
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

/* Block signals (default storage) */
B_pathRadius_T pathRadius_B;

/* Block states (default storage) */
DW_pathRadius_T pathRadius_DW;

/* External inputs (root inport signals with default storage) */
ExtU_pathRadius_T pathRadius_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_pathRadius_T pathRadius_Y;

/* Real-time model */
RT_MODEL_pathRadius_T pathRadius_M_;
RT_MODEL_pathRadius_T *const pathRadius_M = &pathRadius_M_;
real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
                     uint32_T maxIndex)
{
  real_T frac;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  return (table[iLeft + 1U] - table[iLeft]) * frac + table[iLeft];
}

/*
 * Output and update for atomic system:
 *    '<S7>/MATLAB Function'
 *    '<S14>/MATLAB Function'
 */
void pathRadius_MATLABFunction(real_T rtu_Ts, real_T *rty_forward_gain, real_T
  *rty_reset, real_T rtp_A1, real_T rtp_A2)
{
  if ((rtp_A1 == 0.0) || (rtp_A2 == 0.0)) {
    *rty_forward_gain = 0.0;
    *rty_reset = 1.0;
  } else {
    *rty_forward_gain = 1.0 / fmax(rtu_Ts, rtp_A2);
    *rty_reset = 0.0;
  }
}

/* Model step function */
ExtY_pathRadius_T pathRadius_step(ExtU_pathRadius_T pathRadius_U)
{
  real_T rtb_forward_gain_g;
  real_T rtb_Divide;
  real_T rtb_forward_gain;
  real_T rtb_Sum_a;
  real_T rtb_reset_j;
  real_T rtb_Integrator;
  real_T rtb_reset;
  ExtY_pathRadius_T pathRadius_Y;

  /* MATLAB Function: '<S7>/MATLAB Function' */
  pathRadius_MATLABFunction(pathRadius_B.Probe[0], &rtb_forward_gain,
    &rtb_reset_j, 0.9646, 1.0747);

  /* DiscreteIntegrator: '<S11>/Integrator' */
  if ((rtb_reset_j != 0.0) || (pathRadius_DW.Integrator_PrevResetState != 0)) {
    pathRadius_DW.Integrator_DSTATE = pathRadius_ConstB.Constant;
  }

  rtb_Integrator = pathRadius_DW.Integrator_DSTATE;

  /* Saturate: '<S1>/Saturation' incorporates:
   *  Inport: '<Root>/speed '
   */
  if (pathRadius_U.speed <= 1.0) {
    rtb_Divide = 1.0;
  } else {
    rtb_Divide = pathRadius_U.speed;
  }

  /* End of Saturate: '<S1>/Saturation' */

  /* Product: '<S1>/Divide' incorporates:
   *  Gain: '<S1>/Gain'
   *  Inport: '<Root>/yawrate'
   */
  rtb_Divide = 0.017453292519943295 * pathRadius_U.yawrate / rtb_Divide;

  /* DiscreteIntegrator: '<S12>/Integrator' */
  if (pathRadius_DW.Integrator_IC_LOADING != 0) {
    pathRadius_DW.Integrator_DSTATE_a = rtb_Divide;
  }

  if ((rtb_reset_j != 0.0) || (pathRadius_DW.Integrator_PrevResetState_b != 0))
  {
    pathRadius_DW.Integrator_DSTATE_a = rtb_Divide;
  }

  /* Math: '<S1>/Math Function' incorporates:
   *  DiscreteIntegrator: '<S12>/Integrator'
   *
   * About '<S1>/Math Function':
   *  Operator: reciprocal
   */
  rtb_forward_gain_g = 1.0 / pathRadius_DW.Integrator_DSTATE_a;


  /* Switch: '<S1>/Switch' incorporates:
   *  Abs: '<S1>/Abs'
   *  Constant: '<S3>/Constant'
   *  Constant: '<S4>/Constant'
   *  Inport: '<Root>/speed '
   *  Logic: '<S1>/Logical Operator'
   *  RelationalOperator: '<S3>/Compare'
   *  RelationalOperator: '<S4>/Compare'
   */
  if ((!(fabs(rtb_forward_gain_g) > 2500.0)) && (!(pathRadius_U.speed < 1.0))) {
    /* Outport: '<Root>/FilteredRadiusM ' */
    pathRadius_Y.FilteredRadiusM = rtb_forward_gain_g;
  } else {
    /* Outport: '<Root>/FilteredRadiusM ' incorporates:
     *  Constant: '<S1>/Constant'
     */
    pathRadius_Y.FilteredRadiusM = 32767.0;
  }


  /* End of Switch: '<S1>/Switch' */

  /* MATLAB Function: '<S14>/MATLAB Function' */
  pathRadius_MATLABFunction(pathRadius_B.Probe_k[0], &rtb_forward_gain_g,
    &rtb_reset, 0.3183, 1.0);

  /* DiscreteIntegrator: '<S19>/Integrator' incorporates:
   *  Inport: '<Root>/yawrate'
   */
  if (pathRadius_DW.Integrator_IC_LOADING_a != 0) {
    pathRadius_DW.Integrator_DSTATE_n = pathRadius_U.yawrate;
  }

  if ((rtb_reset != 0.0) || (pathRadius_DW.Integrator_PrevResetState_l != 0)) {
    pathRadius_DW.Integrator_DSTATE_n = pathRadius_U.yawrate;
  }

  /* DiscreteIntegrator: '<S18>/Integrator' */
  if ((rtb_reset != 0.0) || (pathRadius_DW.Integrator_PrevResetState_f != 0)) {
    pathRadius_DW.Integrator_DSTATE_ae = pathRadius_ConstB.Constant_h;
  }

  /* Sum: '<S13>/Sum' incorporates:
   *  DiscreteIntegrator: '<S18>/Integrator'
   *  DiscreteIntegrator: '<S19>/Integrator'
   *  Gain: '<S13>/Gain'
   *  Inport: '<Root>/yawrate'
   */
  rtb_Sum_a = (pathRadius_U.yawrate - pathRadius_DW.Integrator_DSTATE_n) -
    0.3183 * pathRadius_DW.Integrator_DSTATE_ae;

  /* Outport: '<Root>/HVPP_Confidence' incorporates:
   *  Abs: '<S2>/Abs'
   *  DiscreteIntegrator: '<S19>/Integrator'
   *  Lookup_n-D: '<S2>/1-D Lookup Table1'
   */
  pathRadius_Y.HVPP_Confidence = look1_binlxpw(fabs
    (pathRadius_DW.Integrator_DSTATE_n),
    pathRadius_ConstP.uDLookupTable1_bp01Data,
    pathRadius_ConstP.uDLookupTable1_tableData, 10U);

  /* Update for DiscreteIntegrator: '<S11>/Integrator' incorporates:
   *  DiscreteIntegrator: '<S12>/Integrator'
   *  Gain: '<S6>/Gain'
   *  Product: '<S6>/Product'
   *  Sum: '<S6>/Sum'
   */
  pathRadius_DW.Integrator_DSTATE += ((rtb_Divide -
    pathRadius_DW.Integrator_DSTATE_a) - 0.9646 *
    pathRadius_DW.Integrator_DSTATE) * rtb_forward_gain * 0.0005;
  if (rtb_reset_j > 0.0) {
    pathRadius_DW.Integrator_PrevResetState = 1;
  } else if (rtb_reset_j < 0.0) {
    pathRadius_DW.Integrator_PrevResetState = -1;
  } else if (rtb_reset_j == 0.0) {
    pathRadius_DW.Integrator_PrevResetState = 0;
  } else {
    pathRadius_DW.Integrator_PrevResetState = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S11>/Integrator' */

  /* Update for DiscreteIntegrator: '<S12>/Integrator' */
  pathRadius_DW.Integrator_IC_LOADING = 0U;
  pathRadius_DW.Integrator_DSTATE_a += 0.0005 * rtb_Integrator;
  if (rtb_reset_j > 0.0) {
    pathRadius_DW.Integrator_PrevResetState_b = 1;
  } else if (rtb_reset_j < 0.0) {
    pathRadius_DW.Integrator_PrevResetState_b = -1;
  } else if (rtb_reset_j == 0.0) {
    pathRadius_DW.Integrator_PrevResetState_b = 0;
  } else {
    pathRadius_DW.Integrator_PrevResetState_b = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S12>/Integrator' */

  /* Update for DiscreteIntegrator: '<S19>/Integrator' incorporates:
   *  DiscreteIntegrator: '<S18>/Integrator'
   */
  pathRadius_DW.Integrator_IC_LOADING_a = 0U;
  pathRadius_DW.Integrator_DSTATE_n += 0.0005 *
    pathRadius_DW.Integrator_DSTATE_ae;
  if (rtb_reset > 0.0) {
    pathRadius_DW.Integrator_PrevResetState_l = 1;
  } else if (rtb_reset < 0.0) {
    pathRadius_DW.Integrator_PrevResetState_l = -1;
  } else if (rtb_reset == 0.0) {
    pathRadius_DW.Integrator_PrevResetState_l = 0;
  } else {
    pathRadius_DW.Integrator_PrevResetState_l = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S19>/Integrator' */

  /* Update for DiscreteIntegrator: '<S18>/Integrator' incorporates:
   *  Product: '<S13>/Product'
   */
  pathRadius_DW.Integrator_DSTATE_ae += rtb_forward_gain_g * rtb_Sum_a * 0.0005;
  if (rtb_reset > 0.0) {
    pathRadius_DW.Integrator_PrevResetState_f = 1;
  } else if (rtb_reset < 0.0) {
    pathRadius_DW.Integrator_PrevResetState_f = -1;
  } else if (rtb_reset == 0.0) {
    pathRadius_DW.Integrator_PrevResetState_f = 0;
  } else {
    pathRadius_DW.Integrator_PrevResetState_f = 2;
  }

 return pathRadius_Y;
  /* End of Update for DiscreteIntegrator: '<S18>/Integrator' */
}

/* Model initialize function */
void pathRadius_initialize(void)
{
  /* Start for Probe: '<S7>/Probe' */
  pathRadius_B.Probe[0] = 0.0005;
  pathRadius_B.Probe[1] = 0.0;

  /* Start for Probe: '<S14>/Probe' */
  pathRadius_B.Probe_k[0] = 0.0005;
  pathRadius_B.Probe_k[1] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S11>/Integrator' */
  pathRadius_DW.Integrator_DSTATE = pathRadius_ConstB.Constant;

  /* InitializeConditions for DiscreteIntegrator: '<S12>/Integrator' */
  pathRadius_DW.Integrator_IC_LOADING = 1U;

  /* InitializeConditions for DiscreteIntegrator: '<S19>/Integrator' */
  pathRadius_DW.Integrator_IC_LOADING_a = 1U;

  /* InitializeConditions for DiscreteIntegrator: '<S18>/Integrator' */
  pathRadius_DW.Integrator_DSTATE_ae = pathRadius_ConstB.Constant_h;
}

/* Model terminate function */
void pathRadius_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
