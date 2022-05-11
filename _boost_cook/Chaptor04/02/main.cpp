#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/has_plus_assign.hpp>

template <class T>
T process_data_plus_assign(const T& v1, const T& v2, const T& v3) {
    // 断言T是int类型
    BOOST_STATIC_ASSERT((boost::is_same<int, T>::value));
    (void) v2;
    (void) v3;
    return v1;
}

// 处理非int类型数据
template <class T>
typename boost::disable_if_c<boost::has_plus_assign<T>::value, T>::type 
 process_data(const T& v1, const T& v2, const T& v3) {
     // 断言T是const char*类型
     BOOST_STATIC_ASSERT((boost::is_same<const char*, T>::value));
     (void) v2;
     (void) v3;
     return v1;
}

// 处理int类型，有+=运算符的数据
template <class T>
typename boost::enable_if_c<boost::has_plus_assign<T>::value, T>::type 
 process_data(const T& v1, const T& v2, const T& v3) {
    return  process_data_plus_assign(v1, v2, v3);
}

int main(int argc, char* argv[]) {
    int i = 1;
    process_data(i, i, i);
    const char* t1 = "Testing";
    const char* t2 = "Example";
    const char* t3 = "Function";
    process_data(t1, t2, t3);
}
