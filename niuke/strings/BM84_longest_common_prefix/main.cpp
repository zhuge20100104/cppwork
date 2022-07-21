#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:

    string findLongestCommon(string s1, string s2){
        int k_len = min(s1.size(), s2.size());
        stringstream ss;
        for(int k=0; k<k_len; ++k) {
            if(s1[k] == s2[k]) {
                ss << s1[k];
            }
        }

        return ss.str();
    }

    /**
     * 
     * @param strs string字符串vector 
     * @return string字符串
     */
    string longestCommonPrefix(vector<string>& strs) {
        // write code here

        if(strs.size() == 0) {
            return "";
        }

        string prefix = strs[0];

        for(int i=1; i<strs.size(); ++i) {
            // 这个prefix 是在不断更新的，详细见题解: 横向扫描
            prefix = findLongestCommon(prefix, strs[i]);
            if(prefix.size() == 0) {
                return "";
            }
        }
        return prefix;
    }
};


// 题目: https://www.nowcoder.com/practice/28eb3175488f4434a4a6207f6f484f47?tpId=295&tqId=732&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {
    string arr_str;
    Solution sol; 
    while(getline(cin, arr_str)) {
        vector<string> arr;
        stringstream ss(arr_str);
        string temp;
        while(getline(ss, temp, ',')) {
            arr.push_back(temp);
        }

        auto res = sol.longestCommonPrefix(arr);
        cout << res << endl; 
    }
    return EXIT_SUCCESS;
}