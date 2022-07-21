#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;


string word_count(string const& word) {

    map<char, int> m;
    for(auto ch: word) {
        ++m[ch];
    }

    vector<pair<char, int>> counts(m.begin(), m.end());

    sort(counts.begin(), counts.end(), [](auto const& left, auto const& right){
        if(left.second > right.second) {
            return true;
        } else if(left.second < right.second) {
            return false;
        } else {
            return left.first < right.first;
        }
    });

    string res{""};
    for(auto ele: counts) {
        res += ele.first;
    }
    return res;
}
// 题目: https://www.nowcoder.com/practice/d3d8e23870584782b3dd48f26cb39c8f?tpId=37&tqId=21253&rp=1&ru=/exam/oj/ta&qru=/exam/oj/ta&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D37%26type%3D37&difficulty=undefined&judgeStatus=undefined&tags=&title=
int main(int argc, char* argv[]) {
    string str;
    while(cin >> str) {
        auto res = word_count(str);
        cout << res << endl;
        str.clear();
    }
    return EXIT_SUCCESS;
}