#include "glog/logging.h"
#include "death_handler/death_handler.h"

#include <boost/type_index.hpp>

template <typename T>
void ref(T const& x) {
    LOG(INFO) << "x in ref(T const&): " << boost::typeindex::type_id_runtime(x).pretty_name();
}

template <typename T>
void nonref(T x) {
    LOG(INFO) << "x in nonref(T): " << boost::typeindex::type_id_runtime(x).pretty_name();
}

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;

    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    ref("hello");
    nonref("hello");
    return EXIT_SUCCESS;
}

