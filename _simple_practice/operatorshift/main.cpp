#include <iostream>
using std::cout;
using std::endl;
#include "utils/person.h"
#include <stdio.h>

ostream& operator<<(ostream& cout, const Person& p){
    cout << "mA=" << p.mA << " mB=" << p.mB;
    return cout;
}

int main() {
    Person p(10, 20);
    cout << p << " Hello world" << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
