#include "utils/son.h"

#include <iostream>
using std::cout;
using std::endl;

#include <stdio.h>

int main() {

    Son s;

    cout << "Son类型的大小: " << sizeof(s) << endl;
    cout << "Base1::mA=" << s.Base1::mA << endl;
    cout << "Base2::mA=" << s.Base2::mA << endl;
     
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
