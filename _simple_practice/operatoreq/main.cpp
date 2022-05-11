#include <iostream>
using std::cout;
using std::endl;
#include <stdio.h>
#include "utils/person.h"


int main() {
    Person p1(10);
    Person p2=p1;
    Person p3(p2);
    Person p4(20);
    p4 = p3;
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
