#include "utils/myint.h"
#include <iostream>
using std::cout;
using std::endl;
#include <stdio.h>

ostream& operator<<(ostream& cout, const MyInt& m){
    cout << m.mNum;
    return cout;
}

int main() {
    MyInt m(20);
    cout << ++m << endl;
    cout << m++ << endl;
    cout << m << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
