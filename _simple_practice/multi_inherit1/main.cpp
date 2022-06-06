#include "utils/son.h"
#include <iostream>
using std::cout;
using std::endl;
#include <cstdlib>

int main(int argc, char* argv[]) {

    Son s;
    cout << "s.Base1::getA: " << s.Base1::getA() << endl;
    cout << "s.Base2::getA: " << s.Base2::getA() << endl;
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}