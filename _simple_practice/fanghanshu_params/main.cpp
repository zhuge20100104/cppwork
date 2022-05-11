#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <algorithm>
using std::find_if;
using std::begin;
using std::end;
#include <cstdlib>

// 初始化向量列表
void initVector(vector<int>& v) {
    for(int i=0; i<10; i++) {
        v.push_back(i);
    }
}

class GreaterFive {
    public:
        bool operator()(int val) {
            return val > 5;
        } 
};

int main(void) {
    vector<int> v;
    initVector(v);

    auto gFive = find_if(begin(v), end(v), GreaterFive());
    
    if(gFive != v.end()) {
        cout << "找到大于5的元素: " << *gFive << endl;
    }else {
        cout << "未找到大于5的元素" << endl;
    }

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}