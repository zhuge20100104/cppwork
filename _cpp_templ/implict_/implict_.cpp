#include "glog/logging.h"
#include "death_handler/death_handler.h"

#include <boost/type_index.hpp>

template <typename DstT, typename SrcT>
inline DstT implicit_cast(SrcT const& x) {
    return x;
}

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    double value = implicit_cast<double>(-1);
    
    LOG(INFO) << boost::typeindex::type_id_runtime(value).pretty_name();
    LOG(INFO) << value;
    return EXIT_SUCCESS;
}