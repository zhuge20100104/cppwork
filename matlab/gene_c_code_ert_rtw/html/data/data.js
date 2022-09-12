var dataJson = {"arch":{"ispc":false,"isunix":true,"ismac":false},"build":"gene_c_code","ref":false,"files":[{"name":"ert_main.c","type":"source","group":"main","path":"/home/fredric/code/cppwork/matlab/gene_c_code_ert_rtw","tag":"","groupDisplay":"Main file","code":"/*\n * Academic License - for use in teaching, academic research, and meeting\n * course requirements at degree granting institutions only.  Not for\n * government, commercial, or other organizational use.\n *\n * File: ert_main.c\n *\n * Code generated for Simulink model 'gene_c_code'.\n *\n * Model version                  : 1.6\n * Simulink Coder version         : 9.6 (R2021b) 14-May-2021\n * C/C++ source code generated on : Fri Sep  9 17:47:31 2022\n *\n * Target selection: ert.tlc\n * Embedded hardware selection: Intel->x86-64 (Windows64)\n * Code generation objectives: Unspecified\n * Validation result: Not run\n */\n\n#include <stddef.h>\n#include <stdio.h>            /* This example main program uses printf/fflush */\n#include \"gene_c_code.h\"               /* Model's header file */\n\n/*\n * Associating rt_OneStep with a real-time clock or interrupt service routine\n * is what makes the generated code \"real-time\".  The function rt_OneStep is\n * always associated with the base rate of the model.  Subrates are managed\n * by the base rate from inside the generated code.  Enabling/disabling\n * interrupts and floating point context switches are target specific.  This\n * example code indicates where these should take place relative to executing\n * the generated code step function.  Overrun behavior should be tailored to\n * your application needs.  This example simply sets an error status in the\n * real-time model and returns from rt_OneStep.\n */\nvoid rt_OneStep(void);\nvoid rt_OneStep(void)\n{\n  static boolean_T OverrunFlag = false;\n\n  /* Disable interrupts here */\n\n  /* Check for overrun */\n  if (OverrunFlag) {\n    rtmSetErrorStatus(gene_c_code_M, \"Overrun\");\n    return;\n  }\n\n  OverrunFlag = true;\n\n  /* Save FPU context here (if necessary) */\n  /* Re-enable timer or interrupt here */\n  /* Set model inputs here */\n\n  /* Step the model */\n  gene_c_code_step();\n\n  /* Get model outputs here */\n\n  /* Indicate task complete */\n  OverrunFlag = false;\n\n  /* Disable interrupts here */\n  /* Restore FPU context here (if necessary) */\n  /* Enable interrupts here */\n}\n\n/*\n * The example \"main\" function illustrates what is required by your\n * application code to initialize, execute, and terminate the generated code.\n * Attaching rt_OneStep to a real-time clock is target specific.  This example\n * illustrates how you do this relative to initializing the model.\n */\nint_T main(int_T argc, const char *argv[])\n{\n  /* Unused arguments */\n  (void)(argc);\n  (void)(argv);\n\n  /* Initialize model */\n  gene_c_code_initialize();\n\n  /* Attach rt_OneStep to a timer or interrupt service routine with\n   * period 0.01 seconds (the model's base sample time) here.  The\n   * call syntax for rt_OneStep is\n   *\n   *  rt_OneStep();\n   */\n  printf(\"Warning: The simulation will run forever. \"\n         \"Generated ERT main won't simulate model step behavior. \"\n         \"To change this behavior select the 'MAT-file logging' option.\\n\");\n  fflush((NULL));\n  while (rtmGetErrorStatus(gene_c_code_M) == (NULL)) {\n    /*  Perform application tasks here */\n  }\n\n  /* Disable rt_OneStep here */\n  /* Terminate model */\n  gene_c_code_terminate();\n  return 0;\n}\n\n/*\n * File trailer for generated code.\n *\n * [EOF]\n */\n"},{"name":"gene_c_code.c","type":"source","group":"model","path":"/home/fredric/code/cppwork/matlab/gene_c_code_ert_rtw","tag":"","groupDisplay":"Model files","code":"/*\n * Academic License - for use in teaching, academic research, and meeting\n * course requirements at degree granting institutions only.  Not for\n * government, commercial, or other organizational use.\n *\n * File: gene_c_code.c\n *\n * Code generated for Simulink model 'gene_c_code'.\n *\n * Model version                  : 1.6\n * Simulink Coder version         : 9.6 (R2021b) 14-May-2021\n * C/C++ source code generated on : Fri Sep  9 17:47:31 2022\n *\n * Target selection: ert.tlc\n * Embedded hardware selection: Intel->x86-64 (Windows64)\n * Code generation objectives: Unspecified\n * Validation result: Not run\n */\n\n#include \"gene_c_code.h\"\n#include \"gene_c_code_private.h\"\n\n/* Exported block signals */\nreal32_T y;                            /* '<Root>/In2' */\nreal32_T z;                            /* '<Root>/Gain' */\n\n/* Exported data definition */\n#pragma cal_section begin\n\n/* Definition for custom storage class: mycsc */\nconst volatile real32_T k = 2.0F;      /* Referenced by: '<Root>/Gain' */\n\n#pragma cal_section end\n\n/* Real-time model */\nstatic RT_MODEL_gene_c_code_T gene_c_code_M_;\nRT_MODEL_gene_c_code_T *const gene_c_code_M = &gene_c_code_M_;\n\n/* Model step function */\nvoid gene_c_code_step(void)\n{\n  /* Gain: '<Root>/Gain' incorporates:\n   *  Inport: '<Root>/In1'\n   *  Inport: '<Root>/In2'\n   *  Sum: '<Root>/Sum'\n   */\n  z = (x + y) * k;\n}\n\n/* Model initialize function */\nvoid gene_c_code_initialize(void)\n{\n  /* (no initialization code required) */\n}\n\n/* Model terminate function */\nvoid gene_c_code_terminate(void)\n{\n  /* (no terminate code required) */\n}\n\n/*\n * File trailer for generated code.\n *\n * [EOF]\n */\n"},{"name":"gene_c_code.h","type":"header","group":"model","path":"/home/fredric/code/cppwork/matlab/gene_c_code_ert_rtw","tag":"","groupDisplay":"Model files","code":"/*\n * Academic License - for use in teaching, academic research, and meeting\n * course requirements at degree granting institutions only.  Not for\n * government, commercial, or other organizational use.\n *\n * File: gene_c_code.h\n *\n * Code generated for Simulink model 'gene_c_code'.\n *\n * Model version                  : 1.6\n * Simulink Coder version         : 9.6 (R2021b) 14-May-2021\n * C/C++ source code generated on : Fri Sep  9 17:47:31 2022\n *\n * Target selection: ert.tlc\n * Embedded hardware selection: Intel->x86-64 (Windows64)\n * Code generation objectives: Unspecified\n * Validation result: Not run\n */\n\n#ifndef RTW_HEADER_gene_c_code_h_\n#define RTW_HEADER_gene_c_code_h_\n#ifndef gene_c_code_COMMON_INCLUDES_\n#define gene_c_code_COMMON_INCLUDES_\n#include \"rtwtypes.h\"\n#endif                                 /* gene_c_code_COMMON_INCLUDES_ */\n\n#include \"gene_c_code_types.h\"\n\n/* Macros for accessing real-time model data structure */\n#ifndef rtmGetErrorStatus\n#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)\n#endif\n\n#ifndef rtmSetErrorStatus\n#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))\n#endif\n\n/* Real-time Model Data Structure */\nstruct tag_RTM_gene_c_code_T {\n  const char_T * volatile errorStatus;\n};\n\n/*\n * Exported Global Signals\n *\n * Note: Exported global signals are block signals with an exported global\n * storage class designation.  Code generation will declare the memory for\n * these signals and export their symbols.\n *\n */\nextern real32_T y;                     /* '<Root>/In2' */\nextern real32_T z;                     /* '<Root>/Gain' */\n\n/* Model entry point functions */\nextern void gene_c_code_initialize(void);\nextern void gene_c_code_step(void);\nextern void gene_c_code_terminate(void);\n\n/* Exported data declaration */\n#pragma cal_section begin\n\n/* Declaration for custom storage class: mycsc */\nextern const volatile real32_T k;      /* Referenced by: '<Root>/Gain' */\n\n#pragma cal_section end\n\n/* Real-time Model object */\nextern RT_MODEL_gene_c_code_T *const gene_c_code_M;\n\n/*-\n * The generated code includes comments that allow you to trace directly\n * back to the appropriate location in the model.  The basic format\n * is <system>/block_name, where system is the system number (uniquely\n * assigned by Simulink) and block_name is the name of the block.\n *\n * Use the MATLAB hilite_system command to trace the generated code back\n * to the model.  For example,\n *\n * hilite_system('<S3>')    - opens system 3\n * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3\n *\n * Here is the system hierarchy for this model\n *\n * '<Root>' : 'gene_c_code'\n */\n#endif                                 /* RTW_HEADER_gene_c_code_h_ */\n\n/*\n * File trailer for generated code.\n *\n * [EOF]\n */\n"},{"name":"gene_c_code_private.h","type":"header","group":"model","path":"/home/fredric/code/cppwork/matlab/gene_c_code_ert_rtw","tag":"","groupDisplay":"Model files","code":"/*\n * Academic License - for use in teaching, academic research, and meeting\n * course requirements at degree granting institutions only.  Not for\n * government, commercial, or other organizational use.\n *\n * File: gene_c_code_private.h\n *\n * Code generated for Simulink model 'gene_c_code'.\n *\n * Model version                  : 1.6\n * Simulink Coder version         : 9.6 (R2021b) 14-May-2021\n * C/C++ source code generated on : Fri Sep  9 17:47:31 2022\n *\n * Target selection: ert.tlc\n * Embedded hardware selection: Intel->x86-64 (Windows64)\n * Code generation objectives: Unspecified\n * Validation result: Not run\n */\n\n#ifndef RTW_HEADER_gene_c_code_private_h_\n#define RTW_HEADER_gene_c_code_private_h_\n#include \"rtwtypes.h\"\n\n/* Imported (extern) block signals */\nextern real32_T x;                     /* '<Root>/In1' */\n\n#endif                                 /* RTW_HEADER_gene_c_code_private_h_ */\n\n/*\n * File trailer for generated code.\n *\n * [EOF]\n */\n"},{"name":"gene_c_code_types.h","type":"header","group":"model","path":"/home/fredric/code/cppwork/matlab/gene_c_code_ert_rtw","tag":"","groupDisplay":"Model files","code":"/*\n * Academic License - for use in teaching, academic research, and meeting\n * course requirements at degree granting institutions only.  Not for\n * government, commercial, or other organizational use.\n *\n * File: gene_c_code_types.h\n *\n * Code generated for Simulink model 'gene_c_code'.\n *\n * Model version                  : 1.6\n * Simulink Coder version         : 9.6 (R2021b) 14-May-2021\n * C/C++ source code generated on : Fri Sep  9 17:47:31 2022\n *\n * Target selection: ert.tlc\n * Embedded hardware selection: Intel->x86-64 (Windows64)\n * Code generation objectives: Unspecified\n * Validation result: Not run\n */\n\n#ifndef RTW_HEADER_gene_c_code_types_h_\n#define RTW_HEADER_gene_c_code_types_h_\n\n/* Model Code Variants */\n\n/* Forward declaration for rtModel */\ntypedef struct tag_RTM_gene_c_code_T RT_MODEL_gene_c_code_T;\n\n#endif                                 /* RTW_HEADER_gene_c_code_types_h_ */\n\n/*\n * File trailer for generated code.\n *\n * [EOF]\n */\n"},{"name":"rtwtypes.h","type":"header","group":"utility","path":"/home/fredric/code/cppwork/matlab/gene_c_code_ert_rtw","tag":"","groupDisplay":"Utility files","code":"/*\n * Academic License - for use in teaching, academic research, and meeting\n * course requirements at degree granting institutions only.  Not for\n * government, commercial, or other organizational use.\n *\n * File: rtwtypes.h\n *\n * Code generated for Simulink model 'gene_c_code'.\n *\n * Model version                  : 1.6\n * Simulink Coder version         : 9.6 (R2021b) 14-May-2021\n * C/C++ source code generated on : Fri Sep  9 17:47:31 2022\n *\n * Target selection: ert.tlc\n * Embedded hardware selection: Intel->x86-64 (Windows64)\n * Code generation objectives: Unspecified\n * Validation result: Not run\n */\n\n#ifndef RTWTYPES_H\n#define RTWTYPES_H\n\n/* Logical type definitions */\n#if (!defined(__cplusplus))\n#ifndef false\n#define false                          (0U)\n#endif\n\n#ifndef true\n#define true                           (1U)\n#endif\n#endif\n\n/*=======================================================================*\n * Target hardware information\n *   Device type: Intel->x86-64 (Windows64)\n *   Number of bits:     char:   8    short:   16    int:  32\n *                       long:  32\n *                       native word size:  64\n *   Byte ordering: LittleEndian\n *   Signed integer division rounds to: Zero\n *   Shift right on a signed integer as arithmetic shift: on\n *=======================================================================*/\n\n/*=======================================================================*\n * Fixed width word size data types:                                     *\n *   int8_T, int16_T, int32_T     - signed 8, 16, or 32 bit integers     *\n *   uint8_T, uint16_T, uint32_T  - unsigned 8, 16, or 32 bit integers   *\n *   real32_T, real64_T           - 32 and 64 bit floating point numbers *\n *=======================================================================*/\ntypedef signed char int8_T;\ntypedef unsigned char uint8_T;\ntypedef short int16_T;\ntypedef unsigned short uint16_T;\ntypedef int int32_T;\ntypedef unsigned int uint32_T;\ntypedef float real32_T;\ntypedef double real64_T;\n\n/*===========================================================================*\n * Generic type definitions: boolean_T, char_T, byte_T, int_T, uint_T,       *\n *                           real_T, time_T, ulong_T.                        *\n *===========================================================================*/\ntypedef double real_T;\ntypedef double time_T;\ntypedef unsigned char boolean_T;\ntypedef int int_T;\ntypedef unsigned int uint_T;\ntypedef unsigned long ulong_T;\ntypedef char char_T;\ntypedef unsigned char uchar_T;\ntypedef char_T byte_T;\n\n/*===========================================================================*\n * Complex number type definitions                                           *\n *===========================================================================*/\n#define CREAL_T\n\ntypedef struct {\n  real32_T re;\n  real32_T im;\n} creal32_T;\n\ntypedef struct {\n  real64_T re;\n  real64_T im;\n} creal64_T;\n\ntypedef struct {\n  real_T re;\n  real_T im;\n} creal_T;\n\n#define CINT8_T\n\ntypedef struct {\n  int8_T re;\n  int8_T im;\n} cint8_T;\n\n#define CUINT8_T\n\ntypedef struct {\n  uint8_T re;\n  uint8_T im;\n} cuint8_T;\n\n#define CINT16_T\n\ntypedef struct {\n  int16_T re;\n  int16_T im;\n} cint16_T;\n\n#define CUINT16_T\n\ntypedef struct {\n  uint16_T re;\n  uint16_T im;\n} cuint16_T;\n\n#define CINT32_T\n\ntypedef struct {\n  int32_T re;\n  int32_T im;\n} cint32_T;\n\n#define CUINT32_T\n\ntypedef struct {\n  uint32_T re;\n  uint32_T im;\n} cuint32_T;\n\n/*=======================================================================*\n * Min and Max:                                                          *\n *   int8_T, int16_T, int32_T     - signed 8, 16, or 32 bit integers     *\n *   uint8_T, uint16_T, uint32_T  - unsigned 8, 16, or 32 bit integers   *\n *=======================================================================*/\n#define MAX_int8_T                     ((int8_T)(127))\n#define MIN_int8_T                     ((int8_T)(-128))\n#define MAX_uint8_T                    ((uint8_T)(255U))\n#define MAX_int16_T                    ((int16_T)(32767))\n#define MIN_int16_T                    ((int16_T)(-32768))\n#define MAX_uint16_T                   ((uint16_T)(65535U))\n#define MAX_int32_T                    ((int32_T)(2147483647))\n#define MIN_int32_T                    ((int32_T)(-2147483647-1))\n#define MAX_uint32_T                   ((uint32_T)(0xFFFFFFFFU))\n\n/* Block D-Work pointer type */\ntypedef void * pointer_T;\n\n#endif                                 /* RTWTYPES_H */\n\n/*\n * File trailer for generated code.\n *\n * [EOF]\n */\n"}],"coverage":[{"id":"SimulinkCoverage","name":"Simulink Coverage","files":[]},{"id":"Bullseye","name":"Bullseye Coverage","files":[]},{"id":"LDRA","name":"LDRA Testbed","files":[]}]};