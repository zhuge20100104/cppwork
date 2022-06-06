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

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        SDL_Event event;
        do {
            SDL_WaitEvent(&event);
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            default:
                // SDL_Log("Event type is %d", event.type);
                break;
            }
        }while(!quit);
        return true;
}

FirstWin::~FirstWin() {
    if(renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if(window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}