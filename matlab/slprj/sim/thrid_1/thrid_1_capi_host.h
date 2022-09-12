#ifndef RTW_HEADER_thrid_1_cap_host_h_
#define RTW_HEADER_thrid_1_cap_host_h_
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap_simtarget.h"
#include "first_1_capi_host.h"
typedef struct { rtwCAPI_ModelMappingInfo mmi ; rtwCAPI_ModelMappingInfo *
childMMI [ 1 ] ; first_1_host_DataMapInfo_T child0 ; }
thrid_1_host_DataMapInfo_T ;
#ifdef __cplusplus
extern "C" {
#endif
void thrid_1_host_InitializeDataMapInfo ( thrid_1_host_DataMapInfo_T *
dataMap , const char * path ) ;
#ifdef __cplusplus
}
#endif
#endif
#endif
