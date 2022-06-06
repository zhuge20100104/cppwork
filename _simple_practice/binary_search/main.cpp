#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>
using std::binary_search;
#include <vector>
using std::vector;
using std::begin;
using std::end;
#include <cstdlib>

void testBinarySearch() {
    vector<int> v;
    for(int i=0; i<10; i++) {
        v.emplace_back(i);
    }

    bool find = binary_search(begin(v), end(v), 9);

    if(find) {
        cout << "找到了元素.." << endl;
    } else {
        cout << "没找到元素" << endl;
    } 
}

int main(void) {
    testBinarySearch();

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}