#include "utils/utils.h"

#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::ifstream;
#include <string>
using std::string;

int main(int argc, char* argv[]) {

    INIT_FILE_PTR(ifstream, f);
    f->open("test.txt", std::ios::in);
    if(!f->is_open()) {
        cout << "文件打开失败!" << endl;
        return -1;
    }

    // 使用 std::string进行读取
    // string buf;
    // while(getline(*f,buf)) {
    //     cout << buf << endl;
    // }


    // 使用const char* 读取
    char buf[1024] = {0};

    while(f->getline(buf, sizeof(buf))) {
        cout << buf << endl;
    }


    
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}