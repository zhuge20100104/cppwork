#include "pointers2/pointers2.h"

#include <iostream>


int main(int argc, char* argv[]) {
    int a = 3;
    int b = 7;
    int result = add(&a, &b);
    std::cout << "add(&a, &b) = " << result << std::endl;

    a = 6;
    b = 5;
    result = 0;
    add_val(&a, &b, &result);
    std::cout << "add_val(&a, &b, &result), result = " 
        << result << std::endl;
    
    a = 8;
    b = 3;
    swap(&a, &b);
    std::cout << "swap(&a, &b), a = " << a << " " 
        << "b = " << b << std::endl;  
    
    a = 6;
    result = 1;
    factorial(&a, &result);
    std::cout << "factorial(&a, &result), result = " << result 
        << std::endl;
    
    return 0;
}