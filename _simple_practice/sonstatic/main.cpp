#include "utils/base.h"
#include "utils/son.h"
#include <stdio.h>


int main() { 
    Son s;
    // 实例访问
    cout << "Son::a=" << s.a << endl;
    cout << "Base::a=" << s.Base::a << endl;
    
    // 类名访问
    cout << "Son::a=" << Son::a << endl;
    cout << "Base::a=" << Son::Base::a << endl;

    // 访问成员函数
    s.func();
    s.Base::func();

    // 使用类名访问成员函数 
    
    Son::func();
    Son::Base::func();

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
