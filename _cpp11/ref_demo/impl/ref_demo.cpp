#include "ref_demo/ref_demo.h"

#include <iostream>

void assign_ref(RefDemo& rf) {
    int y = 20;
    rf.x = y;
}