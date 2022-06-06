#include "glog/logging.h"
#include "death_handler/death_handler.h"

namespace X {
    template <typename T>
    void f(T);
};

namespace N {
    // 此处使用的是using声明，X::f永远不会被找到
    using namespace X;
    enum E {e1};
    void f(E) {
        LOG(INFO) << "N::f(N::E) called";
    }
};

void f(int) {
    LOG(INFO) << "::f(int) called";
}

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    ::f(N::e1); // 限定全局域名，不走ADL, argument dependencies loop 
    f(N::e1);  // 同时命中全局域名和ADL，优先走ADL
    return EXIT_SUCCESS;
}