#include "auto_intro/auto_intro.h"

std::shared_ptr<int> define_auto_var() {
    auto i = 10;
    std::shared_ptr<int> res {new int{i}};
    return std::move(res);
}


int sum(int x, int y) {
    return x + y;
}


std::list<int> getlist() {
    auto ls = {1, 2, 3, 4 , 5};
    return std::move(ls);
}



