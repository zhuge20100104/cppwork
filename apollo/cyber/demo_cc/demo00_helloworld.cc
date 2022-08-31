#include "cyber/cyber.h"

int main(int argc, char* argv[]) {
    // argv[0] 是当前的文件名
    // 日志文件名以传入的参数进行命名
    apollo::cyber::Init(argv[0]);
    AINFO << "hello world!";
    return EXIT_SUCCESS;
}