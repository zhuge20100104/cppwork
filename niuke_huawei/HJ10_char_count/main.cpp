#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int constexpr CHARS_NUM = 128;

int chars_count(string const& str) {
    auto res{0};
    int counts[CHARS_NUM] = {0};
    for(int i=0; i<str.size(); ++i) {
        auto ch = str[i];
        ++counts[ch];
    }

    for(int i=0; i<CHARS_NUM; ++i) {
        if(counts[i]>0) {
            ++res;
        }
    }
    return res;
}


// 题目: https://www.nowcoder.com/practice/995b8a548827494699dc38c3e2a54ee9?tpId=37&tqId=21313&rp=1&ru=/exam/oj/ta&qru=/exam/oj/ta&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D2%26tpId%3D37%26type%3D37&difficulty=undefined&judgeStatus=undefined&tags=&title=
int main(int argc, char* argv[]) {
    string str;
    
    while(cin >> str) {
        auto count = chars_count(str);
        cout << count << endl;
    }
    return EXIT_SUCCESS;
}