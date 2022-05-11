#include "funcs.h"

void modifyConstRefs() {
    int x = 5;
    
    int &ref_x1 = x;
    const int & ref_x2 = x;
    ref_x1 = 10;

    // 表达式不是可修改的左值，不能改
    // ref_x2 = 11;
}

void modifyConstPtrs() {
    int x = 5;
    const int* ptr1 = &x;
    int* const ptr2 = &x;
    const int* const ptr3 = &x;

    *ptr2 = 10;
    // 表达式不是可修改的左值，不能改
    // *ptr1 = 20;
    // *ptr3 = 30;
}

void validConstDeclarations() {
    const int* ptr3 = &MAX;
    // const int* 不能初始化 int *
    // int *ptr4 = &MAX;

    int x = 5;
    
    int &ref_x1 = x;
    const int & ref_x2 = x;
    ref_x1 = 10;

    const int* ptr1 = &x;
    int* const ptr2 = &x;

    const int &r1 = ref_x1;
    // const int & 不能用来初始化 int&， 丢失常量修饰符
    // int &r2 = ref_x2;

    // 非常量不能用常量初始化
    // int *& p_ref1 =  ptr1;
    const int* const &  p_ref2 = ptr2;
}