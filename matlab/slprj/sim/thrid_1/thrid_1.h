#ifndef RTW_HEADER_thrid_1_h_
#define RTW_HEADER_thrid_1_h_
#include <string.h>
#include <stddef.h>
#include "rtw_modelmap_simtarget.h"
#ifndef thrid_1_COMMON_INCLUDES_
#define thrid_1_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "thrid_1_types.h"
#include "multiword_types.h"
#include "first_1.h"
#include "rt_nonfinite.h"
typedef struct { gkrrblwlytk kpndpn3im1 ; } mjo1hrqgd1 ; typedef struct {
bfdfydd4k3 irzbrj2jmt ; } guntxvrzjx ; struct caq0j3cj3p { struct
SimStruct_tag * _mdlRefSfcnS ; struct { rtwCAPI_ModelMappingInfo mmi ;
rtwCAPI_ModelMapLoggingInstanceInfo mmiLogInstanceInfo ;
rtwCAPI_ModelMappingInfo * childMMI [ 1 ] ; sysRanDType * systemRan [ 2 ] ;
int_T systemTid [ 2 ] ; } DataMapInfo ; struct { int_T mdlref_GlobalTID [ 1 ]
; } Timing ; } ; typedef struct { mjo1hrqgd1 rtdw ; iv2sou1byw rtm ; }
kgnlwaxfa12 ; extern void bcqss2uchd ( SimStruct * _mdlRefSfcnS , int_T
mdlref_TID0 , iv2sou1byw * const hita4xd3k3 , mjo1hrqgd1 * localDW , void *
sysRanPtr , int contextTid , rtwCAPI_ModelMappingInfo * rt_ParentMMI , const
char_T * rt_ChildPath , int_T rt_ChildMMIIdx , int_T rt_CSTATEIdx ) ; extern
void mr_thrid_1_MdlInfoRegFcn ( SimStruct * mdlRefSfcnS , char_T * modelName
, int_T * retVal ) ; extern mxArray * mr_thrid_1_GetDWork ( const kgnlwaxfa12
* mdlrefDW ) ; extern void mr_thrid_1_SetDWork ( kgnlwaxfa12 * mdlrefDW ,
const mxArray * ssDW ) ; extern void mr_thrid_1_RegisterSimStateChecksum (
SimStruct * S ) ; extern mxArray * mr_thrid_1_GetSimStateDisallowedBlocks ( )
; extern const rtwCAPI_ModelMappingStaticInfo * thrid_1_GetCAPIStaticMap (
void ) ; extern void avdrljch3c ( const real_T * gtgvrz0xlq , guntxvrzjx *
localZCSV ) ; extern void thrid_1 ( const real_T * a13welbu3l , const real_T
* nhekdsvnsb , const real_T * k1k5sitan4 , const real_T * gtgvrz0xlq , const
real_T * gwnvojgtir , real_T * jq03grg51u , real_T * iv5pinivfj , mjo1hrqgd1
* localDW ) ; extern void oobjgqdnug ( mjo1hrqgd1 * localDW , iv2sou1byw *
const hita4xd3k3 ) ;
#endif
