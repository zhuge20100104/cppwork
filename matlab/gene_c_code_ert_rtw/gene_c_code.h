/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: gene_c_code.h
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

#ifndef RTW_HEADER_gene_c_code_h_
#define RTW_HEADER_gene_c_code_h_
#ifndef gene_c_code_COMMON_INCLUDES_
#define gene_c_code_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* gene_c_code_COMMON_INCLUDES_ */

#include "gene_c_code_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Real-time Model Data Structure */
struct tag_RTM_gene_c_code_T {
  const char_T * volatile errorStatus;
};

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real32_T y;                     /* '<Root>/In2' */
extern real32_T z;                     /* '<Root>/Gain' */

/* Model entry point functions */
extern void gene_c_code_initialize(void);
extern void gene_c_code_step(void);
extern void gene_c_code_terminate(void);

/* Exported data declaration */
#pragma cal_section begin

/* Declaration for custom storage class: mycsc */
extern const volatile real32_T k;      /* Referenced by: '<Root>/Gain' */

#pragma cal_section end

/* Real-time Model object */
extern RT_MODEL_gene_c_code_T *const gene_c_code_M;

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
 * '<Root>' : 'gene_c_code'
 */
#endif                                 /* RTW_HEADER_gene_c_code_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
