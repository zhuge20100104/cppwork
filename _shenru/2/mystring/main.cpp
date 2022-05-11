#include "utils/mystring.hpp"
#include <algorithm>
#include <vector>
#include <algorithm>
using std::vector;

int main() {

    
    vector<MyString> vec;
    vec.emplace_back("Hello");
    vec.emplace_back("World");
    vec.emplace_back("C++");
    
    for_each(begin(vec), end(vec), [](const MyString& str) { cout << str << endl; });

}


