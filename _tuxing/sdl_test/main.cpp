#include "first_win.h"

#include <iostream>

int main(int argc, char* argv[]) {
    FirstWin win("第一个窗口", 200, 400, 640, 480);
    WindowCreateErrors err =  WindowCreateErrors::NO_ERROR;
    bool create_suc = win.create_window(err);
    if(!create_suc) {
        std::cerr << "窗口创建失败, Error: " << err << std::endl;  
        return -1;
    }
    return 0;
}