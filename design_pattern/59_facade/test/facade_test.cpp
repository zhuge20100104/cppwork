#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "facade.hpp"

#include <utility>
#include <gtest/gtest.h>



int main(int argc, char** argv) {
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;

    Debug::DeathHandler dh;

    google::InitGoogleLogging("./logs.log");
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}


GTEST_TEST(FacadeTests, Facade) {
    auto window = Console::instance().multi_buffers(3);

    for (std::size_t i=0; i<20; ++i){
        cv::HersheyFonts font = cv::HersheyFonts::FONT_HERSHEY_DUPLEX;
        if(i%2 == 0) {
            font = cv::HersheyFonts::FONT_HERSHEY_TRIPLEX;
        }
        window->buffers[0].add_string(
            std::string("This is line ") + std::to_string(i), font);
    }
    window->show();
    window->wait_to_dispose();
}