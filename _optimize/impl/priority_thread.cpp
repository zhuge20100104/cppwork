#include "priority_thread.h"

#include <iostream>

PriorityThread::PriorityThread() {
    // 设置当前进程nice值为最低，设为最高优先级进程
    nice(-20);
    // 获取当前优先级
    pthread_getschedparam(pthread_self(), &policy, &param); 
    old_priority = param.sched_priority;
    // 设置当前线程优先级为最高优先级
    param.sched_priority = sched_get_priority_max(policy);
    pthread_setschedparam(pthread_self(), policy, &param);
}

PriorityThread::~PriorityThread() {
    // 设置当前进程nice值为最高，降低优先级
    nice(19);
    // 设置优先级为普通线程优先级
    param.sched_priority = old_priority;
    pthread_setschedparam(pthread_self(), policy, &param);
}

