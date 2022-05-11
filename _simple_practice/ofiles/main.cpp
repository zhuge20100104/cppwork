
#include "utils/utils.h"
#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ofstream;


int main(int argc, char* argv[]) {

    INIT_FILE_PTR(ofstream, f);

    f->open("test.txt", std::ios::out);
    *f << "姓名: 张三" << endl;
    *f << "年龄: 18" << endl;
    *f << "性别: 男" << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
