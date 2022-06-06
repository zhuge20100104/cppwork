#include "glog/logging.h"
#include "death_handler/death_handler.h"

int C;

class C {
    private:
        int i[2];
    
    public:
        static int f() {
            // 这个C是指类C对象，大小为8 字节
            return sizeof(C);
        }
};

int f() {
    return sizeof(C);
}


int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    LOG(INFO) << "C::f() = " << C::f();
    LOG(INFO) << "::f() = " << ::f();

    return EXIT_SUCCESS;
}