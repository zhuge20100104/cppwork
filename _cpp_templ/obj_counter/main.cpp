#include "object_counter.hpp"

#include <iostream>

template <typename CharT>
class MyString: public ObjectCounter<MyString<CharT>> {
    //
};

int main(int argc, char* argv[]) {
    MyString<char> s1, s2;
    MyString<wchar_t> ws;

    std::cout << "Number of MyString<char>: " << MyString<char>::live() << "\n";
    std::cout << "Number of MyString<wchar_t>: " << MyString<wchar_t>::live() << "\n";

    return EXIT_SUCCESS;
} 
