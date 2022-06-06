#ifndef _FREDRIC_TASK_LAUNCHER_H_
#define _FREDRIC_TASK_LAUNCHER_H_
#include "tasks/task.h"
#include "tasks/request.h"

struct task_launcher {
    task_launcher(const std::string& task_info);

    void run();

    std::string dump_results();
    
    void dump_requests();

    int get_per_thread_sleep_mills(int thread_count_, int stress_hold_on_time_);
    
    void run_a_request(request& req_value, req_result& req_res);
    private:
        requests reqs_;
        results results_;
        multi_requests multi_reqs_; // TODO: 后面做multi_reqs，现在不做，因为涉及到中间变量的保存问题
        task task_;   
};

#endif