#ifndef _PRIORITY_THREAD_H_
#define _PRIORITY_THREAD_H_
#include <unistd.h>
#include <pthread.h>

struct PriorityThread {
    int policy;
    int old_priority;
    sched_param param;
    PriorityThread();
   ~PriorityThread();
};

#endif
