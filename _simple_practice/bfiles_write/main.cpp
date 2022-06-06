#include "utils/utils.h"
#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::ofstream;

#include <cstdlib>

class Person {
    public:
        char m_Name[64];  //姓名
        int m_Age;  // 年龄
};

int main(int argc, char* argv[]) {

    INIT_FILE_PTR(ofstream, f);

    f->open("person.txt", std::ios::out | std::ios::binary);

    Person p {"张三", 18};
    
    f->write((const char*)&p, sizeof(p));

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}