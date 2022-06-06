#include "utils/son.h"

#include <stdio.h>

int main() {

    Son s;
    cout << "Son::mNum=" << s.mNum << endl;
    cout << "Base::mNum=" << s.Base::mNum << endl;
    
    s.func();
    s.Base::func();

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
