#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <sstream>

using namespace std;

long non_repeated_sum(string const& num_str) {
    stringstream ss;
    set<char> sets;
    for(int i=num_str.size()-1; i>=0; i--) {
        if(sets.find(num_str[i]) == sets.end()) {
            ss << num_str[i];
            sets.insert(num_str[i]);
        }
    }
    return atol(ss.str().data());
}

// 题目: https://www.nowcoder.com/practice/253986e66d114d378ae8de2e6c4577c1?tpId=37&tqId=21232&rp=1&ru=/exam/oj/ta&qru=/exam/oj/ta&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D37%26type%3D37&difficulty=undefined&judgeStatus=undefined&tags=&title=
int main(int argc, char* argv[]) {

    string num_str;
    while(cin >> num_str) {
        auto res = non_repeated_sum(num_str);
        cout << res << endl;
        num_str.clear();
    }
    return EXIT_SUCCESS;
}