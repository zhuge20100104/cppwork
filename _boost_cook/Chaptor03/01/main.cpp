#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <set>
#include <deque>
#include <string>

#include <cstdlib>

void foo1() {
    std::istringstream iss("100");
    int i;
    iss >> i;
    std::cout << "convert using std::istringstream, value: " 
        << i << std::endl;
}

void foo2() {
    char* end;
    int i = std::strtol("100", &end, 10);
    std::cout << "convert using std::strtol, value: " 
        << i << std::endl;
}

void foo3() {
    {
        int i = boost::lexical_cast<int>("100");
        std::cout << "convert using boost::lexical_cast, value: "
            << i << std::endl;
    }

    char chars[] = {'1', '0', '0'};
    int i = boost::lexical_cast<int>(chars, 3);
    assert(i == 100);

    try {
        // short 小于32767
        short s = boost::lexical_cast<short>("1000000");
        assert(false); // 这一句永远走不到
        (void) s; // 避免未使用警告
    }catch(const boost::bad_lexical_cast& /* e */) {
    }    

    try{
        int i = boost::lexical_cast<int>("This is not a number!");
        assert(false);
        (void) i;
    }catch(const boost::bad_lexical_cast& /* e */) {
    }
}

// boost::lexical_cast支持不同地域风格的cast
void foo4() {
    std::locale::global(std::locale("ru_RU.UTF8"));
    float f = boost::lexical_cast<float>("1,0");
    assert(f < 1.01 && f > 0.99); 
    std::locale::global(std::locale::classic()); // 返回经典C locale 
}

template <class ContainerT>
std::vector<long int> container_to_longs(const ContainerT& container) {
    using value_type = typename ContainerT::value_type;
    std::vector<long int> ret;
    using func_t = long int (*) (const value_type& );
    func_t f = &boost::lexical_cast<long int, value_type>;
    std::transform(container.begin(), container.end(), std::back_inserter(ret), f);
    return ret;
}

void foo5() {
    std::set<std::string> str_set;
    str_set.insert("1");
    assert(container_to_longs(str_set).front() == 1);

    std::deque<const char*> char_deque;
    char_deque.push_front("1");
    char_deque.push_back("2");
    assert(container_to_longs(char_deque).front() == 1);
    assert(container_to_longs(char_deque).back() == 2);

    using element_t = boost::array<unsigned char, 2>;
    boost::array<element_t, 2> arrays = {{ {{'1', '0'}}, {{'2', '0'}} }};
    assert(container_to_longs(arrays).front() == 10);
    assert(container_to_longs(arrays).back() == 20);
}

int main(int argc, char* argv[]) {
    foo1();
    foo2();
    foo3();
    foo4();
    foo5();
}
