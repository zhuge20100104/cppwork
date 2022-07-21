#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

string const IPV4 = "IPv4";
string const IPV6 = "IPv6";
string const NEITHER = "Neither";

string const IPV6_CHARS = "0123456789abcdefABCDEF";
string const IPV4_CHARS = "0123456789";

class Solution {
public:

    vector<string> split_str(string IP, char dim) {
        vector<string> res{};
        stringstream ss{IP};
        string temp;
        while(getline(ss, temp, dim)) {
            res.push_back(temp);    
        }
        return res;
    }

    bool valid_ipv6(string IP) {
        // 处理这种场景
        // aa:bb:cc:dd:ee:ff:bb:bb:
        // 最后一个冒号不应该，钻std::stringstream getline的空子
        if(IP[IP.size() - 1] == ':') {
            return false;
        }

        auto ip_vec = split_str(IP, ':');
       

        if(ip_vec.size() != 8) {
            return false;
        }

        for(auto const& ele: ip_vec) {
            if(ele.empty()) {
                return false;
            }
            if(ele.size() > 4) {
                return false;
            }

            for(auto const& ch: ele) {
                if(IPV6_CHARS.find(ch) == string::npos) {
                    return false;
                }
            }
        }
        return true;
    }

    bool is_valid_ipv4_num(string ip_num) {
        if(ip_num.empty()) {
            return false;
        }

        if(ip_num.size()>=2 && (ip_num[0] == '0')) {
            return false;
        }

        for(auto const& ch: ip_num) {
            
            if(IPV4_CHARS.find(ch) == string::npos) {
                return false;
            }
        }

        auto ip_val = atoi(ip_num.data());
        return ip_val >= 0 && ip_val <=255;
    }

    bool valid_ipv4(string IP) {
        auto ip_vec = split_str(IP, '.');
        if(ip_vec.size() != 4) {
            return false;
        }

        for(auto const& ele: ip_vec) {
            if(!is_valid_ipv4_num(ele)) {
                return false;
            }    
        }
        return true;
    }

    /**
     * 验证IP地址
     * @param IP string字符串 一个IP地址字符串
     * @return string字符串
     */
    string solve(string IP) {
        // write code here
        if(IP.find(':') != string::npos) {
            if(valid_ipv6(IP)) {
                return IPV6;
            }
        } else if(IP.find('.') != string::npos) {
            if(valid_ipv4(IP)) {
                return IPV4;
            }
        } 
        
        return NEITHER;
    }
};


// 题目: https://www.nowcoder.com/practice/55fb3c68d08d46119f76ae2df7566880?tpId=295&tqId=1024725&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {
    string ip_addr_str;
    Solution sol;

    while(cin >> ip_addr_str) {
        auto res = sol.solve(ip_addr_str);
        cout << res << endl;
    }
    return EXIT_SUCCESS;
}