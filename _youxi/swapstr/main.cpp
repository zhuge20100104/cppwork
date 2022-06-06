#include <cstring>
#include <iostream>
#include <algorithm>

void reverse(char* str) {
    std::size_t len = std::strlen(str);
    if(len <=1 ) return;
    std::size_t start = 0;
    std::size_t mid = len / 2;

    while(start < mid) {
        std::swap(str[start], str[len-start-1]);
        ++start;
    }
}

int main() {
    char src[] = "Hello world!";
    reverse(src);
    std::cout << src << std::endl;
    std::reverse(src, src+std::strlen(src));
    std::cout << src << std::endl;
}
