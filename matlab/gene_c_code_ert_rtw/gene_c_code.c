/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: gene_c_code.c
 *
 * Code generated for Simulink model 'gene_c_code'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Fri Sep  9 17:47:31 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "gene_c_code.h"
#include "gene_c_code_private.h"

/* Exported block signals */
real32_T y;                            /* '<Root>/In2' */
real32_T z;                            /* '<Root>/Gain' */

/* Exported data definition */
#pragma cal_section begin

/* Definition for custom storage class: mycsc */
const volatile real32_T k = 2.0F;      /* Referenced by: '<Root>/Gain' */

#pragma cal_section end

/* Real-time model */
static RT_MODEL_gene_c_code_T gene_c_code_M_;
RT_MODEL_gene_c_code_T *const gene_c_code_M = &gene_c_code_M_;

/* Model step function */
void gene_c_code_step(void)
{
  /* Gain: '<Root>/Gain' incorporates:
   *  Inport: '<Root>/In1'
   *  Inport: '<Root>/In2'
   *  Sum: '<Root>/Sum'
   */
  z = (x + y) * k;
}

/* Model initialize function */
void gene_c_code_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void gene_c_code_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
