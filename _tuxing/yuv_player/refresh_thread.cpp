#include "refresh_thread.h"


bool RefreshThread::thread_exit_  = false;

RefreshThread::RefreshThread() {
    timer_thread = SDL_CreateThread(refresh_video_timer, nullptr, nullptr);
}

int RefreshThread::refresh_video_timer(void* udata) {
    thread_exit_  = false;
    // 当线程不终止时，每隔 40毫秒推送一个刷新事件
    // 1000 / 40 = 25帧，每秒播放25帧 FPS
    while(!thread_exit_) {
        SDL_Event event;
        event.type = REFRESH_EVENT;
        SDL_PushEvent(&event);
        SDL_Delay(40);
    }
    // 退出时重置thread_exit_ 为 false
    thread_exit_ = false; 

    // 发送退出事件给主线程
    SDL_Event event;
    event.type = QUIT_EVENT;
    SDL_PushEvent(&event);
    return 0;
}

RefreshThread::~RefreshThread() {}

