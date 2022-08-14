#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>

using namespace std;


int main(int argc, char* argv[]) {
    unsigned char half_limit = 150;
    int j = 0;
    // unsigned char 范围 [0-255]
    // uchar 溢出之后，又变为0
    // 永远达不到300，死循环
    // 为什么 2*half_limit能达到300?
    // 因为2是int类型，向上转型
    // 无穷循环
    for(unsigned char i=0; i<2*half_limit; ++i) {
        cout << "current i: " << (int)i << endl;
        ++j;
    } 
    cout << j << endl;
    return EXIT_SUCCESS;
}