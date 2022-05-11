#include "optional.hpp"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

#include <cstdlib>

struct MyStruct {
    MyStruct() {}

    MyStruct(int a, int b): m_a(a), m_b(b) {}
    int m_a;
    int m_b;
};

void testOp() {
    Optional<string> a("ok");
    Optional<string> b("cancel");
    Optional<string> c("aa");

    Optional<string> d = a;
    cout << "d=" << *d << endl;

    Optional<MyStruct> op;
    op.emplace(1, 2);

    MyStruct t;
    if(op) {
        t = *op;
    }

    cout << "t.m_a= " << t.m_a << " t.m_b= " << t.m_b << endl; 
    op.emplace(3, 4);

    if(op) {
        t = *op;
    }

    cout << "t.m_a= " << t.m_a << " t.m_b= " << t.m_b << endl;
}

int main(void) {
    
    testOp();

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}