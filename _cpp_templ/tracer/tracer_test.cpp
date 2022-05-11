#include "tracer.hpp"

#include "glog/logging.h"
#include "death_handler/death_handler.h"

#include <algorithm>

int main(int argc, char* argv[]) {
    
    Debug::DeathHandler dh;
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;
    
    google::InitGoogleLogging("./logs.log");

    sort_tracer input[] = {7, 3, 5, 6, 4, 2, 0, 1, 9, 8};
    for(auto&& i: input) {
        LOG(INFO) << i.val();
    }

    LOG(INFO) << "\n";

    long created_at_start = sort_tracer::creations();
    long max_alive_at_start = sort_tracer::max_live();
    long assigned_at_start = sort_tracer::assignments();
    long compared_at_start = sort_tracer::comparisons();

    LOG(INFO) << "Start std::sort\n";
    std::sort(std::begin(input), std::end(input));
    LOG(INFO) << "End std::sort\n";

    for(auto&& i: input) {
        LOG(INFO) << i.val();
    }
    LOG(INFO) << "\n";

    LOG(INFO) << "std::sort() of 10 SortTracer's"
              << " was performed by:\n "
              << sort_tracer::creations() - created_at_start
              << " temporary tracers\n "
              << "up to "
              << sort_tracer::max_live()
              << " tracers at the same time (" 
              << max_alive_at_start << " before)\n "
              << sort_tracer::assignments() - assigned_at_start
              << " assignments\n "
              << sort_tracer::comparisons() - compared_at_start
              << " comparisons\n\n";

    return EXIT_SUCCESS;
}
