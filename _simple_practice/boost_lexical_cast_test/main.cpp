#include <boost/lexical_cast.hpp>

#include <iostream>

int main(int argc, char* argv[]) {
    int res = boost::lexical_cast<int>("100");
    std::cout << res << std::endl;
}