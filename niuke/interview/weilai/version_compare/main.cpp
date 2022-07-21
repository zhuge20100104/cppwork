#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
    vector<int> get_ver_vector(string const& version) {
        stringstream ss{version};
        vector<int> ver;
        string temp;
        while(getline(ss, temp, '.')) {
            auto i = stoi(temp);
            ver.push_back(i);
        } 
        return ver;
    }

    bool is_ver_left_equal(int start_idx, vector<int> vec) {
        bool is_equal {true};
        for(int j=start_idx; j<vec.size(); ++j) {
            if(vec[j] != 0) {
                is_equal = false;
                break;
            }
        }
        return is_equal;
    }


public:
    int version_compare(string const& version1, string const& version2) {
        
        auto ver1 = get_ver_vector(version1);
        auto ver2 = get_ver_vector(version2);

        auto len = min(ver1.size(), ver2.size());

        for(int i=0; i<len; ++i) {
            if(ver1[i] < ver2[i]) {
                return -1;
            } else if(ver1[i] > ver2[i]) {
                return 1;
            }
        }


        if(ver1.size() > len) {
            return is_ver_left_equal(len, ver1)? 0: 1;
        }

        if(ver2.size() > len) {
            return is_ver_left_equal(len, ver2)? 0: -1;
        }

        return 0;

       
    }
};

// 题目: https://www.nowcoder.com/practice/c3120c1c1bc44ad986259c0cf0f0b80e?tpId=295&tqId=44664&ru=/exam/oj&qru=/ta/format-top101/question-ranking&sourceUrl=%2Fexam%2Foj
int main(int argc, char* argv[]) {
    string versions;
    Solution sol;
    while(getline(cin, versions)) {
        stringstream ss{versions};
        string version1;
        getline(ss, version1, ',');
        string version2;
        getline(ss, version2, ',');
        auto res = sol.version_compare(version1, version2);
        cout << res << endl;
    }
    return EXIT_SUCCESS;
}