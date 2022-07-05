#include "printer/printer.hpp"

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;


class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> unorder_dict;
        // Word去除重复的词
        for(auto ele: wordDict) {
            unorder_dict.insert(ele);
        }


        vector<bool>  dp(s.size() + 1, false);

        // 空串默认包含在 字典中
        dp[0] = true;
        // 分[0,j-1] 和 [j,i]两边来看 
        for(int i=1; i<=s.size(); ++i) {
            for(int j=0; j<i; ++j) {
                if(dp[j] && (unorder_dict.find(s.substr(j, i-j))!= unorder_dict.end())) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[s.size()];
    }
};

int main(int argc, char** argv) {
    Solution s;

    string str;
    while(getline(cin, str)) {
        string dict_str;
        getline(cin, dict_str);
        stringstream ss{dict_str};
        vector<string> word_dict;
        string temp;
        while(ss >> temp) {
            word_dict.push_back(temp);
        }
        auto res = s.wordBreak(str, word_dict);
        if(res) {
            cout << "true" << endl;
        } else {
            cout << "false" << endl;
        }
    }
    return EXIT_SUCCESS;
}