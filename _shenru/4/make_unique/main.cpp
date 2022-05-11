#include "make_unique.hpp"
#include <iostream>
using std::cout;
using std::endl;
#include <cstdlib>

int main(void) {
    auto u1 = make_unique<int>(10);
    cout << *u1 << endl;

    auto u2 = make_unique<int[]>(10);
    for(int i=0; i<10; i++) {
        u2[i] = i;
    }

    for(int i=0; i<10; i++) {
        cout << u2[i] << " ";
    }

    cout << endl;
    
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}