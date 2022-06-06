#ifndef _FREDRIC_TASK_SUMMARY_H_
#define _FREDRIC_TASK_SUMMARY_H_

#include "tasks/request.h"

#include <vector>
#include <string>

struct task_summary {
    task_summary(const std::vector<std::string>& task_infos);
    
    void dump_summary_results();

    private:
        std::vector<json> all_results_;
        json summary_j {};
};
#endif