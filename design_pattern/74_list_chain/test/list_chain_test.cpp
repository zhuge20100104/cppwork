#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "list_chain.hpp"
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

GTEST_TEST(ListChainTests, ListChainAllChain) {
    Creature goblin {"Goblin", 1, 1};
    CreatureModifierChain chain;
    DoubleAttackModifier r1 {goblin};
    DoubleAttackModifier r1_2 {goblin};
    IncreaseDefenseModifer r2 {goblin};
    chain.add(&r1);
    chain.add(&r1_2);
    chain.add(&r2);
    chain.handle();
    std::cout << goblin << "\n"; 
} 

GTEST_TEST(ListChainTests, ListChainBreakChain) {
    Creature goblin {"Goblin", 1, 1};
    CreatureModifierChain chain;
    NoBonusesModifier nm {goblin};
    DoubleAttackModifier r1 {goblin};
    DoubleAttackModifier r1_2 {goblin};
    IncreaseDefenseModifer r2 {goblin};
    chain.add(&nm);
    chain.add(&r1);
    chain.add(&r1_2);
    chain.add(&r2);
    chain.handle();
    std::cout << goblin << "\n"; 
} 