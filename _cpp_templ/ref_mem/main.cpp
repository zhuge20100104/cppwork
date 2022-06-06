#include "ref_mem.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    RefMembers r1;
    RefMembers r2{r1};
    r1 = r2;
    
    return EXIT_SUCCESS;
}
