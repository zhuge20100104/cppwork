#ifndef _FREDRIC_VARS_H_
#define _FREDRIC_VARS_H_

struct Vars {
    int i {0};
    char ch {'a'};
    bool flag {true};
    float f {1.283f};
    double d {521.342};
    int arr[5] {1, 2, 3, 4, 5};
};

Vars def_vars();

#endif