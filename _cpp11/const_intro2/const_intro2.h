#ifndef _FREDRIC_CONST_INTRO2_H_
#define _FREDRIC_CONST_INTRO2_H_

#include <memory>

void print(const int* ptr);

void print(const int& ref);

const std::shared_ptr<int> get_const_ele();

#endif