#ifndef _FIRST_WIN_H_
#define _FIRST_WIN_H_

#include "common_header.h"

#include <string>
#include <exception>

struct FirstWin {

    FirstWin(std::string caption, int x, int y, int width, int height);
    
    SDL_Window* window{nullptr};
    SDL_Renderer* renderer{nullptr}; 
    SDL_Texture* texture{nullptr};
    SDL_Rect rect{};
    bool create_window(WindowCreateErrors& err);

    ~FirstWin();

    private:
        std::string caption_;
        int x_;
        int y_;
        int width_;
        int height_;
        bool quit {false};
};

#endif
