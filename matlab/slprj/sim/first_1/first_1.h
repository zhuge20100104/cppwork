#ifndef RTW_HEADER_first_1_h_
#define RTW_HEADER_first_1_h_
#include <string.h>
#include <stddef.h>
#include "rtw_modelmap_simtarget.h"
#ifndef first_1_COMMON_INCLUDES_
#define first_1_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "first_1_types.h"
#include "multiword_types.h"
#include "rt_nonfinite.h"
struct mkhn4puisbp_ { real_T P_0 ; real_T P_1 ; } ; struct ozmdpqndnk {
struct SimStruct_tag * _mdlRefSfcnS ; struct { rtwCAPI_ModelMappingInfo mmi ;
rtwCAPI_ModelMapLoggingInstanceInfo mmiLogInstanceInfo ; sysRanDType *
systemRan [ 2 ] ; int_T systemTid [ 2 ] ; } DataMapInfo ; struct { int_T
mdlref_GlobalTID [ 1 ] ; } Timing ; } ; typedef struct { bhr5kpvmxc rtm ; }
gkrrblwlytk ; extern void ju41pvzfyv ( SimStruct * _mdlRefSfcnS , int_T
mdlref_TID0 , bhr5kpvmxc * const bv1hrak15r , void * sysRanPtr , int
contextTid , rtwCAPI_ModelMappingInfo * rt_ParentMMI , const char_T *
rt_ChildPath , int_T rt_ChildMMIIdx , int_T rt_CSTATEIdx ) ; extern void
mr_first_1_MdlInfoRegFcn ( SimStruct * mdlRefSfcnS , char_T * modelName ,
int_T * retVal ) ; extern mxArray * mr_first_1_GetDWork ( const gkrrblwlytk *
mdlrefDW ) ; extern void mr_first_1_SetDWork ( gkrrblwlytk * mdlrefDW , const
mxArray * ssDW ) ; extern void mr_first_1_RegisterSimStateChecksum (
SimStruct * S ) ; extern mxArray * mr_first_1_GetSimStateDisallowedBlocks ( )
; extern const rtwCAPI_ModelMappingStaticInfo * first_1_GetCAPIStaticMap (
void ) ; extern void first_1 ( const real_T * fv2500umat , const real_T *
lexkctlgcm , const real_T * iwqvicuvbv , const real_T * m5pb3nv5fp , const
real_T * hkokqen5ph , real_T * adjsimwakm , real_T * gufz3yaq3h ) ; extern
void grrifbxgfo ( bhr5kpvmxc * const bv1hrak15r ) ;
#endif
