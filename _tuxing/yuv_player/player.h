#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "refresh_thread.h"

#include <memory>
#include <string>

struct Player {
    // 视频文件指针
    FILE* video_fd;
    // 主循环接收的事件
    SDL_Event event;
    // 更新窗体大小的rect
    SDL_Rect rect;
    // YUV 视频的排列格式，需要与指定视频相对应
    Uint32 pixformat {SDL_PIXELFORMAT_IYUV};
    // SDL窗口对象
    SDL_Window* win{nullptr}; 
    // SDL渲染器
    SDL_Renderer* render{nullptr};
    // 纹理对象
    SDL_Texture* texture{nullptr};

    // 刷新线程唯一指针
    std::unique_ptr<RefreshThread> pThread{nullptr};
    // 窗体宽度
    int w_width {1940};
    // 窗体高度
    int w_height {1100};
    // 视频宽度
    int video_width {1920};
    // 视频高度
    int video_height {1080};

    // 数据缓冲区
    Uint8* video_buf{nullptr};
    // YUV数据文件地址
    std::string path_;
    
    // YUV数据单帧的大小
    unsigned int yuv_frame_len {0};

    Player(const std::string& path);
    ~Player();

    void main_loop(PlayerErrors & err);
    private:
        void init(PlayerErrors & err);
};
#endif