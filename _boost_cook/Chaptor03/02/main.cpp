#include <boost/lexical_cast.hpp>

#include <sstream>

#include <cassert>
#include <cstdlib>

void foo1() {
    std::string s = boost::lexical_cast<std::string>(100);
    assert(s == "100");
}

void foo2() {
    // stringstream对象需要一直存在，直到程序结束
    std::stringstream ss;
    ss << 100;
    std::string s;
    ss >> s;
    assert(s == "100");
}

void foo3() {
    char buffer[100];
    std::sprintf(buffer, "%i", 100);
    std::string s(buffer);
    assert(s == "100");
}

int main(int argc, char* argv[]) {
    foo1();
    foo2();
    foo3();
}