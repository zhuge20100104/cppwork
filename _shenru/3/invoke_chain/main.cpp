#include "task.hpp"
#include <iostream>
using std::cout;
using std::endl;

#include <cstdlib>

void TestTask() {
    Task<int(int)> task([](int i) {return i;});
    auto result = task.Then([](int i){return i + 1; }).Then([](int i){return i + 2;}) 
        .Then([](int i){return i + 3; }).Run(1);
    
    cout << "result=" << result << endl;  
}

int main(void) {
    TestTask();

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}