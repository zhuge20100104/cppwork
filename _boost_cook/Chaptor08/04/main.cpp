#include <boost/type_traits/common_type.hpp>

#include <cassert>

// C++11 格式的加法运算
// C++11 配合使用auto 和 decltype关键字 可以推断返回值类型 
template <class T1, class T2>
auto my_function_cpp11(const T1& v1, const T2& v2) -> decltype(v1+v2) {
    return v1 + v2;
}


struct  s1 {};
struct  s2 {};
struct  s3 {};

inline s3 operator + (const s1& /*v1*/, const s2& /*v2*/) {
    return s3();
}

inline s3 operator + (const s2& /*v1*/, const s1& /*v2*/) {
    return s3();
}

// C++ 03及之前版本，实现C++ 11 decltype类型推断
namespace result_of {
    // 返回T1， T2的公共类型
    template <class T1, class T2>
    struct my_function_cpp03 {
        using type = typename boost::common_type<T1, T2>::type;
    };

    // 对于s1和s2类型的相加，因为没有通用的结果定义，所以需要两个模板特化
    template <>
    struct my_function_cpp03<s1, s2> {
        using type = s3;  
    };

    template <>
    struct my_function_cpp03<s2, s1> {
        using type = s3;
    };
};

// 实现cpp03版本的对象相加
template <class T1, class T2>
inline typename result_of::my_function_cpp03<T1, T2>::type  my_function_cpp03(
    const T1& v1, const T2& v2
) {
    return v1 + v2;
}

int main(int argc, char* argv[]) {
    s1 v1;
    s2 v2;

    my_function_cpp11(v1, v2);
    my_function_cpp11(v2, v1);
    assert(my_function_cpp11('\0', 1) == 1);

    my_function_cpp03(v1, v2);
    my_function_cpp03(v2, v1);
    assert(my_function_cpp03('\0', 1) == 1);
}
