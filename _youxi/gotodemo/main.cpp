#include <iostream>

void test_goto() {
    auto i = 0;
label:
    std::cout << "Hello" << std::endl;
    for(; i<10; ++i) {
        if(i==3) {++i;  goto label;}
        std::cout << i << std::endl;
        if(i==8) goto endloop;
    }
endloop:
    std::cout << "good bye" << std::endl;
}

int main() {

    test_goto();
}
