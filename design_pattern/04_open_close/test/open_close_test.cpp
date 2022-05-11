#include "products.hpp"

#include "death_handler/death_handler.h"
#include "json/json.hpp"
#include <glog/logging.h>

#include <gtest/gtest.h>
#include "df/df.h"

using json = nlohmann::json;

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

GTEST_TEST(OpenCloseTests, OpenClose) {
    Product apple {"Apple", Color::green, Size::small};
    Product tree {"Tree", Color::green, Size::large};
    Product house {"House", Color::blue, Size::large};

    std::vector<Product*> items {&apple, &tree, &house};
    // auto spec = AndSpec(ColorSpec(Color::green), SizeSpec(Size::large));

    auto spec = ColorSpec(Color::green) && SizeSpec(Size::large);
    
    auto bf = BetterFilter();
    for(auto& item: bf.filter(items, spec)) {
        std::cout << item->name << " is green and large\n";
    }
}