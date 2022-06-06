#include <iostream>

#include <algorithm>
using std::rotate;
using std::cout;
using std::endl;
#include <vector>
using std::vector;

int main(void) {
    vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int pos = 5;
    // 旋转中心是第一个参数 5
    // 开始旋转的元素是  第二个参数
    // 结束旋转的元素是 最后一个参数
    // 5 6 7 8 9 0 1 2 3 4
    rotate(v.begin(), v.begin()+pos, v.end());
    // 6 7 8 9 5 0 1 2 3 4
    rotate(v.begin(), v.begin()+1, v.end()-pos);

    for(auto i: v) {
        cout << i << " ";
    }

    cout << endl;
}