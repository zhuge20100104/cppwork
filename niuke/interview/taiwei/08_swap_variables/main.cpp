#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;
// 脑筋急转弯
void swap(int& x, int& y, int& z) {
    // 原理:
    x += y;
    // y = x + y - y = x 
    y = x - y;
    // x = (x + y_old) - y_new = x + y - x = y
    x = x - y;

    x += z;
    z = x - z;
    x = x - z;

    y += z;
    z = y - z;
    y = y - z;
}

int main(int argc, char* argv[]) {
    int x = 30, y = 10, z = 20;
    swap(x, y, z);
    cout << x << "," << y << "," << z << endl;

    return EXIT_SUCCESS;
}