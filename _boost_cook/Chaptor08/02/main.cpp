#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/static_assert.hpp>

using boost::mpl::_1;
using boost::mpl::_2;


// Condition 条件判断失败时，
// 生成的缺省类类型
struct fallback {};

// Cond(Param)判断成功时，使用Func(Param)返回的类型,
// 判断失败时，返回Fallback类型
template <class Func, class Param, class Cond, class Fallback=fallback>
struct apply_if {
    // 注意这里只是一个Cond类型，并没有取值，
    // 需要在eval_if_c里面去求值，所以需要在类型名前面加上 typename
    using condition_t = typename boost::mpl::apply<Cond, Param>::type;
    // 这里直接是apply，是一个结构体，所以不需要typename
    using applied_type = boost::mpl::apply<Func, Param>;

    // applied_type类型里面本身有一个 type类型定义，所以不需要用 boost::mpl::identity包裹，
    // 而Fallback里面不一定有type定义，所以需要包裹一下，加上type定义
    // identity类的定义如下，
    // BOOST_MPL_AUX_NA_PARAM(T) 这个宏的意思是 T = struct na类型
    // na是一个空的struct，有一个type定义
    // 如果默认不传的话, T就是na类型
    // 如果传了的话，例如此处，T就是fallback类型
     
    /**
     * 
     * template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
        >
        struct identity
        {
            typedef T type;
            BOOST_MPL_AUX_LAMBDA_SUPPORT(1, identity, (T))
        };
    */
    using type = typename boost::mpl::eval_if_c<
        condition_t::value,
        applied_type,
        boost::mpl::identity<Fallback>
    >::type;
};

using res1_t = apply_if<
    boost::make_unsigned<_1>,
    int,
    boost::is_integral<_1>
    >::type;

BOOST_STATIC_ASSERT((boost::is_same<res1_t, unsigned int>::value));

using res2_t = apply_if<
    boost::make_unsigned<_1>,
    float,
    boost::is_integral<_1>
    >::type;

BOOST_STATIC_ASSERT((boost::is_same<res2_t, fallback>::value));



int main(int argc, char* argv[]) {

}
