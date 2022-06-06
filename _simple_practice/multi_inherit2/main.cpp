#include "utils/animals.h"
#include <iostream>
using std::cout;
using std::endl;

#include <cstdlib>

int main(int argc, char* argv[]) {

    SheepTuo t;

    t.m_Age = 100;

    cout << "SheepTuo的年龄是: " << t.m_Age << endl;
    cout << "&SheepTuo.Sheep::m_Age: " << &(t.Sheep::m_Age) << endl;
    cout << "&SheepTuo.Tuo::m_Age: " << &(t.Tuo::m_Age) << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}