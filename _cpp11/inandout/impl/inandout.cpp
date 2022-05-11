#include "inandout/inandout.h"

#include <iostream>

void pure_out() {
    std::cout << "Hello World\n";
}

int in_and_out_age(std::istream& is) {
    int age{0};
    std::cout << "Tell me your age :";
    is >> age;
    if(age >= 200) {
        age = 0;
    }
    std::cout << "Your age is :" << age << std::endl;
    return age;
}

std::string in_and_out_name(std::istream& is) {
    std::string name;
    std::cout << "What is your name?";
    std::getline(is, name);
    std::cout << "Your name is :" << name << std::endl;
    return std::move(name);
}