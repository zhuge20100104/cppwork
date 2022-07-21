#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

vector<long> get_primes(long const num) {
    long src = num;
    vector<long> vec;

    for(long i=2; i<=sqrt(src); ++i) {
        // 这里是while，要一直除，除到不能除为止
        while(src%i == 0) {
            vec.emplace_back(i);
            src/=i;
        }
    }

    long res{1};
    for(auto const& ele: vec) {
        res *= ele;
    }

    if(res!=num) {
        // 加入最后一个质因子
        vec.emplace_back(num/res);
    }
    return vec;
}


// 题目: https://www.nowcoder.com/practice/253986e66d114d378ae8de2e6c4577c1?tpId=37&tqId=21232&rp=1&ru=/exam/oj/ta&qru=/exam/oj/ta&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D37%26type%3D37&difficulty=undefined&judgeStatus=undefined&tags=&title=
int main(int argc, char* argv[]) {
    long num;
    while(cin >> num) {
        auto res = get_primes(num);
        for(auto const& ele: res) {
            cout << ele << " ";
        }
    }
    return EXIT_SUCCESS;
}