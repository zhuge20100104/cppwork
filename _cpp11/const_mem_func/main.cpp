#include "car.h"

#include <cstdlib>

int main(int argc, char* argv[]) {
    const Car car {4};
    
    // 错误： 常量对象只能调用常量函数
    // car.add_passengers(1);

    car.dashboard();
    return EXIT_SUCCESS;
}