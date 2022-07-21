#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int putting_apples(int m, int n) {
    // 其中有一个为负数，不得行
    if(m<0 || n<0) {
        return 0;
        // 有一个盘子{n=1}，只能分1下， 只有一个苹果 {m=1}，也只能分一下
    } else if(m==1 || n==1) {
        return 1;
    } else {
        // 这个情况有点复杂，需要用到递归和动态规划
        // 两种情况，
        // 第一种情况是说有 空盘子，假设只有一个盘子是空的，那问题转化为把m个苹果放到 n-1盘子上
        // 第二种情况是说没有空盘子，假定每个盘子上至少已经有了一个苹果，那问题转换为把m-n个苹果放到 n个盘子上
        return putting_apples(m, n-1) + putting_apples(m-n, n);
    }
}

// 题目: https://www.nowcoder.com/practice/bfd8234bb5e84be0b493656e390bdebf?tpId=37&tqId=21284&rp=1&ru=/exam/oj/ta&qru=/exam/oj/ta&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D2%26tpId%3D37%26type%3D37&difficulty=undefined&judgeStatus=undefined&tags=&title=
int main(int argc, char* argv[]) {

    int m{0}, n{0};
    while(cin >> m >> n) {
        auto res = putting_apples(m, n);
        cout << res << endl;
    }
    return EXIT_SUCCESS;
}