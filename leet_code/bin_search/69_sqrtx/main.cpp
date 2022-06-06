#include "printer/printer.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    // 使用二分法求 sqrt(a)的值
    int mySqrt(int x) {
        // x == 0， 直接返回
        if(!x) return 0;
        int l {1}, r{x}, mid{0}, sqrt_{0};
        while(l<=r) {
            mid = l + (r-l)/2;
            sqrt_ = x / mid;
            if(mid == sqrt_) {
                return mid;
            } else if(mid > sqrt_) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        } 
        return r;
    }

    // 牛顿迭代法
    // x(n+1) = x(n) - f(x(n))/f'(x(n))
    //        =  x^2 - a - (x^2 - a) / 2*x
    //        = x/2 + a/(2*x)
    int mySqrt2(int x) {
        // 使用long类型防止整型相乘溢出
        long a =  x;
        while(a*a > x) {
            a = (a + x/a) / 2;
        }
        return a;
    }
};

auto main(int argc, char** argv) -> int {
    Solution s;
    int ele {8};
    // auto res = s.mySqrt(ele);
    // cout << ele << " after sqrt is: " << res << "\n";
    
    auto res = s.mySqrt2(ele);
    cout << ele << " after sqrt is: " << res << "\n";
    return EXIT_SUCCESS;
}