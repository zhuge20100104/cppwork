#include <boost/mpl/apply.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/not.hpp>
#include <boost/static_assert.hpp>

#include <iostream>
#include <typeinfo>

template <class Param1, class Param2, class Func1, class Func2> 
struct coalesce {
    // 对Func1(Param1) 进行元运算以后的结果类型
    using type1 = typename boost::mpl::apply<Func1, Param1>::type;
    // 对Func2(Param2) 进行元运算以后的结果类型
    using type2 = typename boost::mpl::apply<Func2, Param2>::type;

    // 如果type1的类型和 mpl::false_类型相等，就取 type2，
    // 否则取 type1
    using type = typename boost::mpl::if_<
        boost::is_same<boost::mpl::false_, type1>,
        type2, 
        type1
    >::type;
};

// 引入boost::mpl参数占位符
using boost::mpl::_1;
using boost::mpl::_2;

// 此处结果分析一下
// Func1(Param1)的结果是
// boost::mpl::not_<boost::mpl::true_> == boost::mpl::false_
// 所以应该取 type2的类型
// 就是  Func2(Param2)
// boost::mpl::not_<boost::mpl::true_> == boost::mpl::false_
// 所以res1_t::value == false
// BOOST_STATIC_ASSERT(!false) 成功
using res1_t = coalesce<
    boost::mpl::true_,
    boost::mpl::true_,
    boost::mpl::not_<_1>,
    boost::mpl::not_<_1>
    >::type;

BOOST_STATIC_ASSERT(!(res1_t::value));

// 分析方法同上面一样
using res2_t = coalesce<
    boost::mpl::true_,
    boost::mpl::false_,
    boost::mpl::not_<_1>,
    boost::mpl::not_<_1>
    >::type;

BOOST_STATIC_ASSERT((res2_t::value));

// 分析方法同上面一样
using res3_t = coalesce<
    boost::mpl::false_,
    boost::mpl::false_,
    boost::mpl::not_<_1>,
    boost::mpl::not_<boost::mpl::not_<_1> > 
>::type;

BOOST_STATIC_ASSERT((res3_t::value));

using res4_t = coalesce<
    boost::mpl::false_,
    boost::mpl::true_,
    boost::mpl::not_<_1>,
    boost::mpl::not_<boost::mpl::not_<_1>>
>::type;

BOOST_STATIC_ASSERT((res4_t::value));

int main(int argc, char* argv[]) {
    std::cerr << typeid(res2_t).name() << std::endl;
    std::cerr << typeid((res2_t::value)).name() << std::endl;
}