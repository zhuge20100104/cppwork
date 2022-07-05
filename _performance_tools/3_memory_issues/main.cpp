#include <iostream>
#include <cstring>
#include <cstdlib>
#include <malloc.h>

using namespace std;

void test() {
    int* ptr = (int*)malloc(sizeof(int)* 10);
    ptr[10] = 7; // 索引越界
    memcpy(ptr+1, ptr, 5); // 踩内存
    free(ptr);
    free(ptr); // 重复释放
    int* p1;
    *p1 = 1; // 非法指针，未初始化 
}
int main(int argc, char* argv[]) {
    test();
    return EXIT_SUCCESS;
}