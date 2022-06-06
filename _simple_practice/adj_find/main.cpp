#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;

#include <cstdlib>
#include <algorithm>
using std::adjacent_find;
using std::begin;
using std::end;

void testAdjFind() {
    vector<int> v;
    v.emplace_back(0);
    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);
    v.emplace_back(3);
    v.emplace_back(4);
    v.emplace_back(4);
    v.emplace_back(5);

    auto findIt = adjacent_find(begin(v), end(v));
    if(findIt == end(v)) {
        cout << "没有找到相同的元素..." << endl;
    } else {
        cout << "找到相同元素,元素值为: " << *findIt << endl;
    }
}

int main(void) {

    testAdjFind();
    
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}