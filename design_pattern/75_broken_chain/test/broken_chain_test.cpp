#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "broken_chain.hpp"

#include "http/http_util.h"
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

GTEST_TEST(PointerChainTests, PointerChainAllChain) {

    Game game;
    Creature goblin {game, 1, 1,  "Goblin"};
    DoubleAttackModifier r1 {game, goblin};
    std::cout << goblin << "\n"; 
    IncreaseDefenseModifier i1 {game, goblin};
    std::cout << goblin << "\n";
    IncreaseDefenseModifier i2 {game, goblin};
    std::cout << goblin << "\n";

    DoubleAttackModifier r2 {game, goblin};
    std::cout << goblin << "\n";
    IncreaseDefenseModifier i3 {game, goblin};
    std::cout << goblin << "\n"; 
} 
