#ifndef _FREDRIC_APP_PERF_CASES_H_
#define _FREDRIC_APP_PERF_CASES_H_
#include "api_accuracy/utils/case.h"

#include <vector>

extern std::vector<Case> app_perf_pos_cases;

extern std::vector<Case> app_perf_neg_cases;

extern std::vector<Case> app_perf_perf_cases;

extern std::vector<AsyncCase> app_perf_async_cases;

extern std::vector<Case> app_perf_async_perf_cases;

extern std::vector<Case> app_perf_async_concurr_perf_cases;
#endif