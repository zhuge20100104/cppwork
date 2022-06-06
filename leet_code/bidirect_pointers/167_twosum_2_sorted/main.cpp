#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

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
};

auto main(int argc, char** argv) -> int {
    Solution s;
    vector<int> numbers {2,7,11,15};
    int target {9};
    auto res = s.twoSum(numbers, target);
    cout << "Can find that numbers[" << res[0] << "] + numbers[" << res[1] <<"]";
    cout << "=" << target << " in array " << numbers << "\n";
    return EXIT_SUCCESS;
}