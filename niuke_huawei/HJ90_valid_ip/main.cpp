#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;


bool valid_digit(string digit_str) {
    if(digit_str.size() == 0) {
        return false;
        // 01, 013这种形式
    } else if(digit_str.size() > 1 && digit_str[0] == '0') {
        return false;
    } else {
        return true;
    }
}

bool valid_ip(string const& ip_addr) {
    if(!ip_addr.data() || ip_addr.empty()) {
        cout << "Empty string, check your input" << endl;
        return false;
    }

    vector<string> ips;
    auto tmp_addr{ip_addr};
    while(tmp_addr.find('.') != string::npos) {
        auto next_addr = tmp_addr.substr(0, tmp_addr.find('.'));
        if(valid_digit(next_addr))   ips.emplace_back(next_addr);
        tmp_addr = tmp_addr.substr(tmp_addr.find('.')+1);
    }

    if(valid_digit(tmp_addr)) {
        ips.emplace_back(tmp_addr);
    }

    if(ips.size() != 4) {
        return false;
    }

    for(auto num_str: ips) {
        for(auto ch: num_str) {
            if(!isdigit(ch)) {
                return false;
            }
        }

        auto tmp_ip_num = atoi(num_str.data());
        if(tmp_ip_num>255) {
            return false;
        } 
    }

    return true;
}


// 题目: https://www.nowcoder.com/practice/995b8a548827494699dc38c3e2a54ee9?tpId=37&tqId=21313&rp=1&ru=/exam/oj/ta&qru=/exam/oj/ta&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D2%26tpId%3D37%26type%3D37&difficulty=undefined&judgeStatus=undefined&tags=&title=
int main(int argc, char* argv[]) {
    string ip_addr;
    
    while(cin >> ip_addr) {
        auto res = valid_ip(ip_addr);
        if(res) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return EXIT_SUCCESS;
}