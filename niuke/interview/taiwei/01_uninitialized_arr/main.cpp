#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>

using namespace std;

// 全局数组会被初始化为0
int x[100];

int main(int argc, char* argv[]) {
    // 局部数组不会被初始化
    int y[100];
    cout << "Local arr y: " << y[99] << endl;
    cout << "Global arr x: " << x[99] << endl;
    return EXIT_SUCCESS;
}