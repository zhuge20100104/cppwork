#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string get_converted_result(string s1, string s2) {
    string input = "0123456789abcdef";
    string output = "084C2A6E195D3B7F";
    auto s3 = s1 + s2;
    string jishu_res{""};
    string oushu_res{""};
    for(size_t i=0; i<s3.size(); ++i) {
        if(i%2==0) {
            oushu_res += s3[i];
        } else if(i%2==1) {
            jishu_res += s3[i];
        }
    }
    
    sort(oushu_res.begin(), oushu_res.end());
    sort(jishu_res.begin(), jishu_res.end());
        
    auto j {0};
    auto k {0};
    for(size_t i=0; i< s3.size(); ++i) {
        if(i%2==0) {
            s3[i] = oushu_res[j++];
        } else if(i%2==1) {
            s3[i] = jishu_res[k++];
        }
    }
    
    // 这里处理的时候，只处理 0-9, 'a'-'f'和 'A'-'F'
    // 其他字符串要保留，直接在s3上面动刀子就可以
    for(size_t i=0; i<s3.size(); ++i) {
        if((s3[i]>='0') && (s3[i]<='9')) {
            s3[i] = output[s3[i] - '0'];
        } else if((s3[i]>='a') && (s3[i]<='f')) {
            s3[i] = output[s3[i] - 'a' +10];
        } else if((s3[i]>='A') && (s3[i]<='F')) {
            s3[i] = output[s3[i] - 'A' + 16];
        }
    }
    return s3;
}


// 题目: https://www.nowcoder.com/practice/d3d8e23870584782b3dd48f26cb39c8f?tpId=37&tqId=21253&rp=1&ru=/exam/oj/ta&qru=/exam/oj/ta&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D37%26type%3D37&difficulty=undefined&judgeStatus=undefined&tags=&title=
int main(int argc, char* argv[]) {
    string s1, s2;
    while(cin >> s1 >> s2) {
        auto res = get_converted_result(s1, s2);
        cout << res << endl;
    }
    return EXIT_SUCCESS;
}