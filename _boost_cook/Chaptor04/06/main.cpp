#include <boost/array.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <iostream>

#include <cstring>

// 这种serialize操作只在 操作类型是 POD类型时，才不会超出array大小
// 所以需要先判断POD类型
// 这个方法是一个错误的方法，可能会翻车
template <class T, std::size_t BufSizeV>
void serialize_bad(const T& value, boost::array<unsigned char, BufSizeV>& buffer) {
    // assert只在Debug模式有效
    assert(BufSizeV >= sizeof(value));
    std::memcpy(&buffer[0], &value, sizeof(value));
}

template <class T, std::size_t BufSizeV> 
void serialize(const T& value, boost::array<unsigned char, BufSizeV>& buffer) {
    BOOST_STATIC_ASSERT(BufSizeV >= sizeof(value));
    BOOST_STATIC_ASSERT((boost::is_pod<T>::value));
    std::memcpy(&buffer[0], &value, sizeof(value));
}

// BOOST_STATIC_ASSERT 宏可以全局使用
BOOST_STATIC_ASSERT(3 >= 1);

struct some_struct {
    enum enum_t {
        value = 1
    };
};

BOOST_STATIC_ASSERT((some_struct::value));

template <class T1, class T2> 
struct some_templated_struct {
    enum enum_t {
        value = (sizeof(T1) == sizeof(T2))
    };
};

BOOST_STATIC_ASSERT((some_templated_struct<int, unsigned int>::value));

template <class T1, class T2>
void type_traits_example(T1 /*v1*/, T2  /*v2*/) {
    std::cout << boost::is_unsigned<T1>::value << std::endl;
    std::cout << boost::is_same<T1, T2>::value << std::endl;
    // remove_const函数的效果
    // const int -> int
    // int -> int
    // int const volatile -> int volatile
    // const int& -> const int&
    using t1_nonconst_t = typename boost::remove_const<T1>::type;
}

template <class T, std::size_t BufSizeV>
void serialize2(const T& value, boost::array<unsigned char, BufSizeV>& buf) {
    BOOST_STATIC_ASSERT_MSG(boost::is_pod<T>::value,
        "This serialize2 function may be used only with pod types");

    BOOST_STATIC_ASSERT_MSG(BufSizeV >= sizeof(value), 
        "Can not make value into buffer, make buffer bigger");

    std::memcpy(&buf[0], &value, sizeof(value));
}

int main(int argc, char* argv[]) {
    const int i = 1;
    type_traits_example(i, i);

    boost::array<unsigned char, 1> buf;
    serialize2(std::string("Hello world"), buf);
}
