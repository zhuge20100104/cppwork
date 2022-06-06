#include <iostream>
using std::cout;
using std::endl;

#include <algorithm>
#include <vector>
using std::vector;
using std::transform;
using std::begin;
using std::end;
using std::for_each;

// 初始化容器
void initVector(vector<int>& v) {
    for(int i=0; i<10; ++i) {
        v.emplace_back(i);
    } 
}

int main(void) {
    vector<int> v;
    initVector(v);

    vector<int> vTarget;
    vTarget.resize(v.size());
    transform(begin(v), end(v), begin(vTarget), [](const int& val)->int {
       return val + 100;
    });

    for_each(begin(vTarget), end(vTarget), [](const int& val) {
        cout << val << " ";
    });
    cout << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}