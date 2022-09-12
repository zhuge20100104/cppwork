#ifndef RTW_HEADER_first_1_cap_host_h_
#define RTW_HEADER_first_1_cap_host_h_
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap_simtarget.h"
typedef struct { rtwCAPI_ModelMappingInfo mmi ; } first_1_host_DataMapInfo_T
;
#ifdef __cplusplus
extern "C" {
#endif
void first_1_host_InitializeDataMapInfo ( first_1_host_DataMapInfo_T *
dataMap , const char * path ) ;
#ifdef __cplusplus
}
#endif
#endif
#endif
