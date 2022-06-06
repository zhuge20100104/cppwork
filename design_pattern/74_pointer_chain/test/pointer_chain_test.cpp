#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "pointer_chain.hpp"

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
    Creature goblin {"Goblin", 1, 1};
    CreatureModifer root{goblin};
    DoubleAttackModifier r1 {goblin};
    DoubleAttackModifier r1_2 {goblin};
    IncreaseDefenseModifer r2 {goblin};
    root.add(&r1);
    root.add(&r1_2);
    root.add(&r2);
    root.handle();
    std::cout << goblin << "\n"; 
} 

GTEST_TEST(PingPongSvcTests, PointerChainBreakChain) {
    Creature goblin {"Goblin", 1, 1};
    CreatureModifer root{goblin};
    NoBonusesModifier nm {goblin};
    DoubleAttackModifier r1 {goblin};
    DoubleAttackModifier r1_2 {goblin};
    IncreaseDefenseModifer r2 {goblin};
    // 从这里断开链接，啥都没发生
    root.add(&nm);
    root.add(&r1);
    root.add(&r1_2);
    root.add(&r2);
    root.handle();
    std::cout << goblin << "\n"; 
}