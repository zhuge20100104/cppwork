#include <boost/fusion/include/remove_if.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/blank.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/static_assert.hpp>

#include <cassert>

// 如果是数字类型就去掉，留下非数字类型
template <class Sequence>
typename boost::fusion::result_of::remove_if<
    const Sequence,
    boost::is_arithmetic<boost::mpl::_1>
>::type getnonarithmetics(const Sequence& seq) {
    return boost::fusion::remove_if<boost::is_arithmetic<boost::mpl::_1>>(seq);
}

// 如果是 非数字 就去掉，留下数字类型
template <class Sequence>
typename boost::fusion::result_of::remove_if<
    const Sequence,
    boost::mpl::not_<boost::is_arithmetic<boost::mpl::_1> >
>::type getarithmetics(const Sequence& seq) {
    return boost::fusion::remove_if<
        boost::mpl::not_<boost::is_arithmetic<boost::mpl::_1>>
    >(seq);
}

int main(int argc, char* argv[]) {
    using tulp1_t = boost::fusion::vector<int, boost::blank, boost::blank, float>;
    tulp1_t tup1(8, boost::blank(), boost::blank(), 0.0);
    
    boost::fusion::vector<boost::blank, boost::blank> na = getnonarithmetics(tup1);
    
    boost::fusion::vector<int, float> a = getarithmetics(tup1);

    assert(boost::fusion::at_c<0>(a) == 8);
    assert(boost::fusion::at_c<1>(a) == 0.0);

    (void) na;
}

// 元向量中的每一个元素，移除const 修饰符
template <class Sequence>
struct make_non_const: boost::mpl::transform<Sequence, 
    boost::remove_const<boost::mpl::_1> > {};

using type1 = boost::fusion::vector<
    const int,
    const boost::blank,
    boost::blank
>;

// 移除掉常量修饰符之后的类型叫nc_type
using nc_type = make_non_const<type1>::type;

BOOST_STATIC_ASSERT((boost::is_same<boost::fusion::result_of::value_at_c<nc_type, 0>::type, int>::value));

BOOST_STATIC_ASSERT((boost::is_same<boost::fusion::result_of::value_at_c<nc_type, 1>::type, boost::blank>::value));

BOOST_STATIC_ASSERT((boost::is_same<boost::fusion::result_of::value_at_c<nc_type, 2>::type, boost::blank>::value));
