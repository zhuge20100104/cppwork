#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;


double get_cube_root(string const& num_str) {
    double num = atof(num_str.data());
    double sign = num > 0? 1: -1;
    num = abs(num);
    for(double i=-20; i<=20; i+=0.01)  {
        if(num - i*i*i <= 1e-8) {
            return sign * i;
        }
    }
    return 0;
}

double get_cube_root2(string const& num_str) {
    double num = atof(num_str.data());
    // 小数的立方根比小数本身大，但是再大也不会大于1，
    // 例如 0.7 ^3=0.3
    // 所以 min可以在 - 1.0到num之间选
    double left = min(-1.0, num);
    double right = max(1.0, num);
    double mid{0.0}; 
    while(abs(right - left) >= 1e-2) { // 精度
        mid = (right + left) /2;
        if(mid * mid * mid > num) {
            right = mid; 
        } else {
            left = mid;
        }
    }

    return mid;
}

// 题目: https://www.nowcoder.com/practice/caf35ae421194a1090c22fe223357dca?tpId=37&tqId=21330&rp=1&ru=/exam/oj/ta&qru=/exam/oj/ta&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D3%26tpId%3D37%26type%3D37&difficulty=undefined&judgeStatus=undefined&tags=&title=
int main(int argc, char* argv[]) {
    string num_str{""};

    while(cin >> num_str) {
        auto res = get_cube_root(num_str);
        cout << fixed << setprecision(1) << res << endl;
        num_str.clear();
    }
    return EXIT_SUCCESS;
}