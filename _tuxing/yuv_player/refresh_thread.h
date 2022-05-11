#ifndef _REFRESH_THREAD_H_
#define _REFRESH_THREAD_H_
#include "common_header.h"

struct RefreshThread {
    // 线程退出标志位
    static bool thread_exit_;
    SDL_Thread *timer_thread {nullptr};

    RefreshThread();
    ~RefreshThread();

    private:
        static int refresh_video_timer(void* udata);
};
#endif
