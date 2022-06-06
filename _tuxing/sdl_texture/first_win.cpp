#include "first_win.h"

FirstWin::FirstWin(std::string caption, 
    int x, int y, 
    int width, int height): caption_{caption}, 
    x_{x}, y_{y}, 
    width_{width}, height_{height} {
        SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
}

bool FirstWin::create_window(WindowCreateErrors& err) {
        window = SDL_CreateWindow(caption_.c_str(),
            x_, y_, width_, height_, 
            SDL_WINDOW_SHOWN);
        if(!window) {
           SDL_Log("Fail to create window\n");
           err = WindowCreateErrors::CREATE_WINDOW_ERROR;
           return false; 
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(!renderer) {
            SDL_Log("Failed to create render!\n");
            err = WindowCreateErrors::CREATE_RENDER_ERROR;
            return false;
        }

        texture = SDL_CreateTexture(renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            600,
            450);
        if(!texture) {
            SDL_Log("Fail to create texture!\n");
            return false;
        }

        rect.w = 30;
        rect.h = 30;

        SDL_Event event;
        do {
            // 避免阻塞卡死循环
            SDL_PollEvent(&event);
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            default:
                // SDL_Log("Event type is %d", event.type);
                break;
            }

            rect.x = rand() % 600;
            rect.y = rand() % 450;

            // 整个屏幕绘黑色
            SDL_SetRenderTarget(renderer, texture);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);

            // 设置红色绘制矩形到纹理
            SDL_RenderDrawRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
            SDL_RenderFillRect(renderer, &rect);

            // 回复绘制到默认设备，显示器
            SDL_SetRenderTarget(renderer, nullptr);
            // 拷贝纹理到显卡
            SDL_RenderCopy(renderer, texture, nullptr, nullptr);
            // 展示纹理
            SDL_RenderPresent(renderer);
        }while(!quit);
        return true;
}

FirstWin::~FirstWin() {
    if(texture) {
        SDL_DestroyTexture(texture);
    }
    if(renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if(window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}