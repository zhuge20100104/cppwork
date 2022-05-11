#include <boost/bind/bind.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/tuple/tuple.hpp>

#include <functional>
using boost::placeholders::_1;

BOOST_AUTO(var, boost::bind(std::plus<int>(), _1, _1));

using type = BOOST_TYPEOF(0.5 + 0.5f);

template <class T1, class T2>
BOOST_TYPEOF_TPL(T1()+T2()) add(const T1& t1, const T2& t2) {
    return t1 + t2;
}

// 验证add(1,1)的结果是 int类型
BOOST_STATIC_ASSERT((boost::is_same<BOOST_TYPEOF(add(1, 1)), int>::value));

namespace readers_project {
    // 在readers_project名称空间中构建一个三个模板参数的结构体
    template<class T1, class T2, class T3>
    struct reader_template_class {};
};

using readers_template_class_1 = readers_project::reader_template_class<int, int, float>;

using readers_template_class_reduced = BOOST_TYPEOF(boost::get<0>(
    boost::make_tuple(readers_template_class_1(), 1)
));

BOOST_STATIC_ASSERT((boost::is_same<readers_template_class_1, readers_template_class_reduced>::value));

int main(int argc, char* argv[]) {

}

