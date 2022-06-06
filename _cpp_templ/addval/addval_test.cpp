#include "death_handler/death_handler.h"
#include "glog/logging.h"

#include "addval.hpp"

#include <algorithm>

template <typename IT, typename OP>
void transform(IT beg, IT end, IT to, OP op) {
    while (beg != end) {
        *to++ = op(*beg++);
    }
}

int main(int argc, char* argv[]) {
    Debug::DeathHandler dh;

    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    int m[] = {1, 2, 3, 4, 5, 6};

    ::transform(m, m+6, m, add_value<int, 5>);

    std::for_each(std::begin(m), std::end(m), [](const auto& ele) {
        LOG(INFO) << ele;
    });
}
