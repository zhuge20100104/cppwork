#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    bool isPalindromeRange(string s, int i, int j) {
        for(int k = i; k<=i+(j-i)/2; ++k) {
            if(s[k] != s[j - (k-i)]) return false;
        }
        return true;
    }

    bool validPalindrome(string s) {
        int left {0}, right{(int)s.size() - 1};
        while(left < right) {
            if(s[left] != s[right]) {
                return isPalindromeRange(s, left+1, right) || isPalindromeRange(s, left, right - 1);                
            }
            ++left;
            --right;
        }
        return true;
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    string str = "abca";
    auto result = s.validPalindrome(str);
    if(result) {
        cout << str << " can be a palindrome with one char deleted.\n";
    } else {
        cout << str << " can't be a palindrome with one char deleted.\n";
    }
    return EXIT_SUCCESS;
}