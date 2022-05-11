#include <boost/mpl/size.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>

#include <iostream>

// 本例使用元函数对元向量中的元素，进行逐一转换操作

// 非拼写错误，unsigned是系统类型，不能用
struct unsigne {};

// 构建常量类型
struct constant {};

// 不改变原先对象类型
struct no_change {};

// Types，原始类型列表，          例如 boost::mpl::vector<int, short, char, float>
// Modifiers,需要添加的修饰符列表  例如 boost::mpl::vector<constant, unsigne, no_change, constant>
// 两个元向量的大小应该是一样的，都是4， 大小的类型也应该是一样的，都是boost::mpl::long_
template <class Types, class Modifiers>
struct do_modifications {
    // 验证两个向量的大小的单位是一样的，否则无法进行比较
    // 注意这里是比较两个type类型，
    // 需要加上 typename 关键字进行修饰
    BOOST_STATIC_ASSERT(
        (boost::is_same<
           typename boost::mpl::size<Types>::type,
           typename boost::mpl::size<Modifiers>::type
        >::value)
    );

    // 验证两个向量的大小是一样的
    // 这里是两个值，
    // 直接 == 就可以
    // 例如 4==4
    BOOST_STATIC_ASSERT(
        (   boost::mpl::size<Types>::type::value ==
            boost::mpl::size<Modifiers>::type::value)
    );

    // 这个binary_operator_t 算子比较蛋疼，但是比spark那种需要画图的还是要简单点
    // 什么意思呢，就是嵌套的if
    // 概括一下，如果修饰符是 unsigne，就把原始类型加上unsigned修饰，
    // 如果修饰符是 constant,就把原始类型加上const 修饰
    // 否则原样返回原始类型
    using binary_operator_t = boost::mpl::if_<
        boost::is_same<boost::mpl::_2, unsigne>,
        boost::make_unsigned<boost::mpl::_1>,
        boost::mpl::if_<
            boost::is_same<boost::mpl::_2, constant>,
            boost::add_const<boost::mpl::_1>,
            boost::mpl::_1
            >
    >;

    // 对Types和Modifiers中的每一个元素应用 binary_operator_t
    using type = typename boost::mpl::transform<
        Types,
        Modifiers,
        binary_operator_t
    >::type;
};

using modifers = boost::mpl::vector<unsigne, no_change, constant, unsigne>;
using types = boost::mpl::vector<int, char, short, long>;

using result_type = do_modifications<types, modifers>::type;

// 验证第一位被修改为 unsigned int
BOOST_STATIC_ASSERT((
    boost::is_same<
        boost::mpl::at_c<result_type, 0>::type, unsigned int
        >::value
));

// 验证第二位仍然是 char
BOOST_STATIC_ASSERT(
    (boost::is_same<
        boost::mpl::at_c<result_type, 1>::type, char
        >::value)
);

// 验证第三位是const short
BOOST_STATIC_ASSERT(
    (boost::is_same<
        boost::mpl::at_c<result_type, 2>::type, const short
        >::value)
);

// 验证最后一位是unsigned long
BOOST_STATIC_ASSERT(
    (boost::is_same<
        boost::mpl::at_c<result_type, 3>::type, unsigned long
        >::value)
);

// 可变模板参数操作boost::mpl::vector例子
template <class ... T> 
struct vt_example {
    using type = typename boost::mpl::vector<T...>;
};

BOOST_STATIC_ASSERT((
    boost::is_same<
        boost::mpl::at_c<vt_example<int, short, long>::type, 0>::type, int
    >::value
));

int main(int argc, char* argv[]) {
    std::cout << typeid(boost::mpl::size<types>::type).name() << std::endl;
    std::cout << boost::mpl::size<types>::type::value << std::endl;
}

