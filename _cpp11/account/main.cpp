#include "check.h"

#include <iostream>

int main(int argc, char* argv[])  {
    Checking c {"Zhangsan", 1000, 10};
    std::cout << c.GetBalance() << std::endl;
    c.WithDraw(100);
    std::cout << c.GetBalance() << std::endl;
    // 加上minBalance限制之后，这次取款应该失败
    c.WithDraw(900);
    std::cout << c.GetBalance() << std::endl;
}