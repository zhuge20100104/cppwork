#include "utils/range.hpp"

using detail_range::Range;

#include <iostream>
using std::cout;
using std::endl;

#include <cstdio>

void testRange() {
    for(int i: Range(15)) {
        cout << " " << i;
    }

    cout << endl;

    for(auto i: Range(2, 6)) {
        cout << " " << i;
    }

    cout << endl;
    
    for(auto i: Range(10.5, 15.5)) {
        cout << " " << i;
    }
    cout << endl;

    for(auto i: Range(35, 27, -1)) {
        cout << " " << i;
    }

    cout << endl;

    for(auto i: Range(2, 8, 0.5)) {
        cout << " " << i;
    }
    cout << endl;

    for(auto i: Range('a', 'z')) {
        cout << " " << i;
    }
    cout << endl;

}   

int main() {
    testRange();
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
