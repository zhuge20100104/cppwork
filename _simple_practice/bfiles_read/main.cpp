#include "utils/utils.h"

#include <fstream>
using std::ifstream;
#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;

class Person {
    public:
        char m_Name[64];  //姓名
        int m_Age;  // 年龄
};

int main(int argc, char* argv[]) {
    
    INIT_FILE_PTR(ifstream, f);

    f->open("person.txt", std::ios::in | std::ios::binary);
    
    Person p;
    
    f->read((char*)&p, sizeof(p));
    cout << "姓名: " << p.m_Name << " " << "年龄: " << p.m_Age << endl; 

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}