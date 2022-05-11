#ifndef _FREDRIC_TASK_H_
#define _FREDRIC_TASK_H_

struct task {
    int thread_count{}; // Single node threads count
    int stress_hold_on_time{0}; // how many times do we want to hold for the requests
};

#endif