#ifndef _FREDRIC_TEST_TEMP_ARGS_H_
#define _FREDRIC_TEST_TEMP_ARGS_H_

#include <iostream>
#include <vector>
#include <any>
#include <string>


template <typename T>
void bind(T param) {
    std::cout << "Generic Binding ..." << std::endl;
    std::cout << param << std::endl;
}

template <>
void bind(int param) {
    std::cout << "Int Binding ..." << std::endl;
    std::cout << param << std::endl;
}

template <>
void bind(double param) {
    std::cout << "Double Binding ..." << std::endl;
    std::cout << param << std::endl;
}

template <>
void bind(const char* param) {
    std::cout << "const char* Binding ..." << std::endl;
    std::cout << param << std::endl;
}


template <typename ... Params>
void bind_params(const std::string& pre_stmt, Params ... params) {
    std::cout << "Pre Statement: " << pre_stmt << std::endl;
    int arr[] = {(bind(params),0)...};
}

#endif