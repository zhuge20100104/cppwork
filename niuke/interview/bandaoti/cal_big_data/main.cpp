#include <iostream>
#include <cstdint>

using namespace std;

int const ERROR_RESULT = 0;
int const MAX_N = 9;  
class Solution {
    uint32_t arr_res[MAX_N + 1] {
        4, // 10^0 + 3
        13, // 10^1 + 3
        103, // 10^2 + 3
        1003, // 10^3 + 3
        10003, // 10^4 + 3
        100003, // 10^5 + 3
        1000003, // 10^6 + 3
        10000003, // 10^7 + 3
        100000003, // 10^8 + 3
        1000000003 // 10^9 + 3
    }; 

public:
    /**
     * 题目: 计算10^n + 3
     * uint32 最大值 4.2e9
     * 所以最大考虑 n = 9
     */
    uint32_t get_result(uint32_t n) {
        return n > MAX_N? ERROR_RESULT: arr_res[n];
    }
};

// 题目: https://www.nowcoder.com/practice/c3120c1c1bc44ad986259c0cf0f0b80e?tpId=295&tqId=44664&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {
    uint32_t n;
    Solution sol;
    while(cin >> n) {
        auto res = sol.get_result(n); 
        if(res == ERROR_RESULT) {
            cout << "Calculation error" << endl;
        } else {
            cout << "10 ^ " << n << " + 3 = " << res << endl;
        }
    }
    return EXIT_SUCCESS;
}