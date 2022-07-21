#include "printer/printer.hpp"

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0, r = numbers.size()-1, sum{0};
        while(l < r) {
            sum = numbers[l] + numbers[r];
            if(sum == target) break;
            else if(sum < target) ++l;
            else --r;
        } 
        return {l+1, r+1};
    }

    vector<int> twoSum2(vector<int>& numbers, int target) {
        map<int, int> m;
        for(int i=0; i<numbers.size(); ++i) {
            m[target-numbers[i]] = i;
        }

        for(int i=0; i<numbers.size(); ++i) {
            if(m.find(numbers[i]) != m.end()) {
                if(i != m[numbers[i]]) {
                    return {i+1, m[numbers[i]] + 1};
                }
            }
        }
        return {-1, -1};
    }
};

auto main(int argc, char** argv) -> int {
    
    Solution sol;

    string arr_str;
    while(getline(cin, arr_str)) {
        stringstream ss{arr_str};
        string temp;
        vector<int> numbers;
        while(getline(ss, temp, ',')) {
            auto i = stoi(temp);
            numbers.push_back(i);
        }

        cout << "Pls input target: ";
        
        int target;
        string target_str;
        getline(cin, target_str);
        target = stoi(target_str);

        auto res = sol.twoSum2(numbers, target);
        cout << "[ ";
        for(auto const& ele: res) {
            cout << ele << " ";
        }
        cout << " ]\n";
    }
    return EXIT_SUCCESS;
}