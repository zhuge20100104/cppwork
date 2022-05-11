#include <iostream>
using std::cout;
using std::endl;
#include <stdio.h>
#include "utils/son.h"

int main() {
    Son s;
    cout << "Son的大小为: " << sizeof(s) << endl;
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
