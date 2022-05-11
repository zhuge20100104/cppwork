#ifndef _COMMON_HEADER_H_
#define _COMMON_HEADER_H_

#define __STDC_CONSTANT_MACROS

#pragma warning(disable:4996)
#include <iostream>
#include <string>

#include <stdio.h>
#include <string.h>

extern "C" {
    #include <SDL2/SDL.h>
}

// 自定义刷新消息和退出消息号
#define REFRESH_EVENT (SDL_USEREVENT + 1)
#define QUIT_EVENT (SDL_USEREVENT + 2)

enum class PlayerErrors {
    NO_ERROR, // 0 无错误
    SDL_INIT_ERROR, // 1 初始化SDL失败
    CREATE_WINDOW_ERROR, // 2 窗口创建失败
    CREATE_RENDER_ERROR, // 3 render创建失败
    OPEN_FILE_ERROR, // 4 打开文件错误
    READ_FILE_ERROR, // 5 读取文件错误
};


class PlayInitExcept: public std::exception {
    public:
        PlayInitExcept():message {"Player 初始化异常!"} 
        {}

        const char* what() const noexcept(true)  {
            return message.c_str();
        }

    private:
        std::string message;
};

template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}
#endif