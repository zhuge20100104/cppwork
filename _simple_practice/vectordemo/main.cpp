#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::for_each;

int main(void) {
    
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    for_each(begin(v), end(v), [](const int& val) {
        cout << val << " ";
    });
    cout << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}