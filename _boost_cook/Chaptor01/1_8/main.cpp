#include <boost/array.hpp>
#include <algorithm>

typedef boost::array<char, 4> array4_t;

array4_t& vector_advance(array4_t& val) {
    const auto inc = [](char& c) { ++c; };
    // val数组中的每个元素加1
    std::for_each(val.begin(), val.end(), inc);
    return val;
}

int main(int argc, char* argv[]) {
    array4_t val = {{0, 1, 2, 3}};

    array4_t val_res;
    val_res = vector_advance(val);

    assert(val.size() == 4);
    assert(val[0] == 1);
    assert(sizeof(val) == sizeof(char) * array4_t::static_size);
}