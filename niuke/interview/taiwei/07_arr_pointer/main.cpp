#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>

using namespace std;


// 输出: 4 4 5 7 10 14 19 25 32 40
// 不要这样写代码，
// 数据量不大直接栈上分配，数据量大直接std::vector
// 这样写的坏处是 q 是 p数组的一个浅拷贝
// 这样无法释放 p，导致 10 *sizeof(int)的内存泄漏
// 尝试delete [] p将会引发错误，因为 q和p指向同一块堆内存
// 不delete [] p, 将会引发 memory leak
int main(int argc, char* argv[]) {
    int x;
    int *p;
    int *q;
    p = new int[10];

    q = p;
    *p = 4;

    for(int j=0; j<9; j++) {
        x = *p;
        p++;
        *p = x+j;
    }

    for(int k=0; k<10; ++k) {
        cout << *q << ' ';
        q++;
    }
    cout << endl;

    return EXIT_SUCCESS;
}