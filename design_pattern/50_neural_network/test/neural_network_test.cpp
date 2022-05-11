#include "death_handler/death_handler.h"
#include <glog/logging.h>
#include "neural.hpp"

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

GTEST_TEST(NeuralNetworkTests, NeuralNetwork) {
    Neuron n1, n2;
    n1.connect_to(n2);
    std::cout << n1 << n2 << std::endl;

    NeuronLayer l1 {5};
    Neuron n3;
    l1.connect_to(n3);

    std::cout << "Neuron " << n3.id << std::endl << n3 << std::endl;

    std::cout << "Layer " << std::endl << l1 << std::endl;
    NeuronLayer l2 {2}, l3 {3};
    l2.connect_to(l3);
    std::cout << "Layer l2" << std::endl << l2;
    std::cout << "Layer l3" << std::endl << l3;
}
