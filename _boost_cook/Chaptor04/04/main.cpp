#include <boost/type_traits/integral_constant.hpp>
#include <boost/static_assert.hpp>

#include <vector>

template <class T>
struct is_stdvector: boost::false_type {};

template <class T, class Allocator>
struct is_stdvector<std::vector<T, Allocator>>: boost::true_type {};

int main(int argc, char* argv[]) {
    BOOST_STATIC_ASSERT(is_stdvector<std::vector<char> >::value);
    BOOST_STATIC_ASSERT(!is_stdvector<char>::value);
    BOOST_STATIC_ASSERT(!is_stdvector<int>::value);
} 