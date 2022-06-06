#ifndef _FREDRIC_UNIFORM_INIT_H_
#define _FREDRIC_UNIFORM_INIT_H_

#include <memory>
#include <string>

struct Initializer {
    int a1 {};
    int a2 {0};
    int a3 {5};
    std::string s1{};
    std::string s2{"C++"};
    char d1[8] {};
    char d2[8] {'\0'};
    char d3[8] {'a', 'b', 'c', 'd'};
    char d4[8] {"abcd"};

    std::shared_ptr<int> p1 {new int{}};
    std::shared_ptr<char> p2 {new char[8]{"Hello"},
        std::default_delete<char[]>()}; 
    
    float f{20.0f};
};

Initializer init();

#endif