#include <iostream>
using std::cout;
using std::endl;
#include <cstdlib>
#include <algorithm>
#include <vector>
using std::vector;
using std::begin;
using std::end;
using std::for_each;

class MyCompare {
    public:
        bool operator()(int a, int b) {
            return a > b;
        }
};


void initVector(vector<int>& v) {
    for(int i=0; i<10; i++) {
        v.push_back(i);
    }
}

int main(void) {
    vector<int> v;
    initVector(v);

    sort(begin(v), end(v), MyCompare());
    for_each(begin(v), end(v), [](const int& val) {
        cout << val << " ";
    });
    cout << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}