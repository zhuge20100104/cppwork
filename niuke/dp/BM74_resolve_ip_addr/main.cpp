#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
    bool is_valid_ip_num(string num_str) {
        if(num_str.size()>1 && num_str[0]=='0') {
            return false;
        }

        auto num = stoi(num_str);
        return num <=255;
    }

public:


    void solve(string s, vector<string>& ans, vector<string> temp, int index) {
        // 索引越界，但是没有找到可用的4个数 
        if(index == s.size() && temp.size() != 4) return;
        if(index == s.size() && temp.size() == 4) {
            encode(temp, ans, s);
            return;
        }

        for(int i=1; i<=3;) {
            int num = stoi(s.substr(index, i));
            // 一种不合适的ip假设
            // 数值大于255，或者 两位以上, s[0] == '0'
            // 例如 25 01， index = 2, i = 2, 取01，不合法
            if(num > 255 || (i>1 && s[index]=='0')) {
                break;
            }
            // temp 里面放入合法字符
            temp.push_back(s.substr(index, i));
            // 下一个IP数值的起始位置
            index += i;
            solve(s, ans, temp, index);
            // 回溯
            index -= i;
            // 这个不合适，回溯到上一个
            temp.pop_back();
            if(index + i < s.size()) ++i;
            else break;

        }

    }

    void encode(vector<string> temp, vector<string>& ans, string s) {
        stringstream ss;
        for(auto const& ele: temp) {
            ss << ele << '.';
        }

        auto one_ip = ss.str();
        one_ip = one_ip.substr(0, one_ip.size() - 1);

        if(one_ip.size()-3 == s.size()) {
            // 将一个临时结果放入ans中
            ans.push_back(one_ip);
        }
    }

    /**
     * 方法2： 回溯+递归 
     * @param s string字符串 
     * @return string字符串vector
     */
    vector<string> restoreIpAddresses2(string s) {
        vector<string> ans;
        vector<string> temp;

        solve(s, ans, temp, 0);
        return ans;
    }


    /**
     * 方法1：暴力法
     * @param s string字符串 
     * @return string字符串vector
     */
    vector<string> restoreIpAddresses(string s) {
        // write code here
        vector<string> ans;
        // IP地址都是3位
        for(int i=1; i<=3; ++i) {
            for(int j=1; j<=3; ++j) {
                for(int m=1; m<=3; ++m) {
                    for(int n=1; n<=3; ++n) {
                        if(i+j+m+n == s.size()) {
                            auto n1 = s.substr(0, i);
                            auto n2 = s.substr(i, j);
                            auto n3 = s.substr(i+j, m);
                            auto n4 = s.substr(i+j+m, n);

                            if(is_valid_ip_num(n1) && is_valid_ip_num(n2) && is_valid_ip_num(n3) && is_valid_ip_num(n4)) {
                                stringstream ip_ss;
                                ip_ss << n1 << '.' << n2 << '.' << n3 << '.' << n4;
                                ans.push_back(ip_ss.str());
                            }
                        }
                    }
                }
            }
        }
        return ans;
    }
};


// 题目: https://www.nowcoder.com/practice/c3120c1c1bc44ad986259c0cf0f0b80e?tpId=295&tqId=44664&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {
    string ip_str;
    Solution sol;

    while(getline(cin, ip_str)) {
        auto res = sol.restoreIpAddresses2(ip_str);

        cout << "[";
        stringstream ss;
        for(auto const& ele: res) {
            ss << ele << ',';
        }

        auto ele_str = ss.str();
        ele_str = ele_str.substr(0, ele_str.size()-1);
        cout << ele_str;
        cout << "]" << endl;
    }

    return EXIT_SUCCESS;
}