#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>

using namespace std;

enum Edian {
    BIG_EDIAN,
    LITTLE_EDIAN
};

class Solution {
public:
    /**
     * 
    0x01234567 的地址引脚表示
    小端法： 
    数据的低位在高地址上，数据的高位在低地址上
    0x00cbbdc0 0x00cbbdc1 0x00cbbdc2 0x00cbbdc3
    67          45          23        01
    

    大端法：
    数据的低位在低地址上，数据的高位在高地址上
    0x00cbbdc0 0x00cbbdc1 0x00cbbdc2 0x00cbbdc3
    01          23          45        67

    int a = 1;

    小端
    00  00  00 01
    大端
    01  00  00 00 
    */
    Edian get_edian() {
        int a = 1;
        char* p = reinterpret_cast<char*>(&a);
        return (*p == 1)? LITTLE_EDIAN: BIG_EDIAN;
    }
};

// 题目: https://www.nowcoder.com/practice/c3120c1c1bc44ad986259c0cf0f0b80e?tpId=295&tqId=44664&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {
    Solution sol;
    auto edian = sol.get_edian();
    auto edian_str = (edian == BIG_EDIAN)? "Big Edian": "Little Edian";
    cout << edian_str << endl;
    return EXIT_SUCCESS;
}