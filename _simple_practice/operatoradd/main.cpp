#include "utils/person.h"
#include <iostream>
using std::cout;
using std::endl;
#include <stdio.h>

int main() {
    Person p1;
    p1.mA = 10;
    p1.mB = 10;

    Person p2;
    p2.mA = 10;
    p2.mB = 10;

    Person p3 = p1 + p2;

    cout << "p3.mA=" << p3.mA << " p3.mB=" << p3.mB << endl;
    cout << "请按任意键继续.." << endl;
    getchar();
    return 0;
}

