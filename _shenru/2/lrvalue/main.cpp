#include <iostream>
using std::cout;
using std::endl;
#include <cstdlib>

void printT(int & t) {
    cout << "lvalue" << endl;
}

template <typename T>
void printT(T&& t) {
    cout << "rvalue" << endl;
}


template <typename T> 
void testForward(T&& v) {
    printT(v);
    printT(std::forward<T>(v));
    printT(std::move(v));
}


void test() {
    testForward(1);
    int x = 1;
    testForward(x);
    testForward(std::forward<int>(x));
}

int main(void) {
    test();
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}

/* 
 * 程序输出如下
 *lvalue
  rvalue
  rvalue

  lvalue 
  lvalue 
  rvalue
  
  // 此处x已经变成了右值，是由上个函数带回来的状态就是右值了
  lvalue
  rvalue
  rvalue 
 *
 * */




