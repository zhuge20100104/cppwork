#ifndef _COMMON_HEADER_H_
#define _COMMON_HEADER_H_
#define __STDC_CONSTANT_MACROS

#pragma warning(disable:4996)
#include <iostream>

extern "C" {
    #include <SDL2/SDL.h>
}

enum class WindowCreateErrors {
    NO_ERROR, // 0 无错误
    CREATE_WINDOW_ERROR, // 1 窗口创建失败
    CREATE_RENDER_ERROR, // 2 render创建失败
};

template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

#endif