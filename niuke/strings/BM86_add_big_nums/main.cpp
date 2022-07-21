#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;


class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 计算两个数之和
     * @param s string字符串 表示第一个整数
     * @param t string字符串 表示第二个整数
     * @return string字符串
     */
    string solve(string s, string t) {
        // s没数据，返回t
        if(s.empty() || (!s.data())) {
            return t;
        }

        // t没数据，返回s
        if(t.empty() || (!t.data())) {
            return s;
        }

        int i = s.size() - 1;
        int j = t.size() - 1;

        // m1左值，m2右值， carry溢出
        int m1{0}, m2{0}, carry{0}; 
        stringstream ss;
        // 只要i,j还有数字，就加
        while(i>=0 || j>=0) {
          
            if(i>=0) {
                m1 = s[i] - '0';
            } else {  // s加完了
                m1 = 0;
            }

            if(j>=0) {
                m2 = t[j] - '0';
            } else { // t加完了
                m2 = 0;
            }
            int sum = m1 + m2 + carry;
            // 9+3 = 12, carry = 12/10 = 1 
            carry = sum/10;
            // 把余数放到string里面去
            // 12 % 10 = 2
            ss << sum % 10;
            --i;
            --j;
        }

        if(carry != 0) {
            ss << carry;
        }

        auto res = ss.str();
        
        reverse(res.begin(), res.end());
        return res;
    }
};


// 题目: https://www.nowcoder.com/practice/11ae12e8c6fe48f883cad618c2e81475?tpId=295&tqId=1061819&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {
    string s, t;
    string line;
    Solution sol;

    while(getline(cin, line)) {
        auto pos = line.find_first_of(',');
        s = line.substr(0, pos);
        t = line.substr(pos+1);
        auto res = sol.solve(s, t);
        cout << res << endl;
    }

    return EXIT_SUCCESS;
}