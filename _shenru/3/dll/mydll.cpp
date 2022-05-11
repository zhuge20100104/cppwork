#include "mydll.h"

int Add(int &a, int &b) {
    return a+b;
}

int Max(const int &a, const int &b) {
    return a > b ? a: b;
}

int Get(const int &a) {
    return a;
}