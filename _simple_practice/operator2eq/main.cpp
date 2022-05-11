#include "utils/person.h"
#include <iostream>
using std::cout;
using std::endl;
#include <stdio.h>

int main() {
    Person p1("张三", 25);
    Person p2("张三", 25);

    if(p1==p2) {
        cout << "p1和p2是相等的" << endl;
    }else {
        cout << "p1和p2不相等的" << endl;
    }
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
