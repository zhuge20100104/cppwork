#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include <set>
#include <cassert>
#include <string>

void sample1() {
    boost::tuple<int, std::string> almost_a_pair(10, "Hello");
    boost::tuple<int, float, double, int> quad(10, 1.0f, 10.0, 1);

    const int i = boost::get<0>(almost_a_pair);
    const std::string& str = boost::get<1>(almost_a_pair);
    const double d = boost::get<2>(quad);

    // 避免编译器未使用的变量警告
    (void)i;
    (void)str;
    (void)d;
}

void sample2() {
    std::set<boost::tuple<int, double, int>> s;
    s.insert(boost::make_tuple(1, 1.0, 2));
    s.insert(boost::make_tuple(2, 10.0, 2));
    s.insert(boost::make_tuple(3, 100.0, 2));

#ifndef BOOST_NO_CXX11_AUTO_DECLARATIONS
    const auto t = boost::make_tuple(0, -1.0, 2);
    assert(2 == boost::get<2>(t));    
#endif
}

void sample3() {
    boost::tuple<int, float, double, int> quad(10, 1.0f, 10.0, 1);
    int i;
    float f;
    double d;
    int i2;

    boost::tie(i, f, d, i2) = quad;
    assert(i == 10);
    assert(i2 == 1);
}

int main(int argc, char* argv[]) {
    sample1();
    sample2();
    sample3();
}