#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/has_plus_assign.hpp>
#include <boost/type_traits/has_plus.hpp>
#include <boost/type_traits/has_post_increment.hpp>
#include <boost/type_traits/has_pre_increment.hpp>

#include <boost/mpl/if.hpp>

#include <cassert>

namespace detail {
    // 前置++仿函数
    struct pre_inc_functor {
        template <class T>
        void operator()(T& value) const {
            ++ value;
        }
    };

    // 后置++仿函数
    struct post_inc_functor {
        template <class T>
        void operator()(T& value) const {
            value ++;
        }
    };

    // += 仿函数
    struct plus_assignable_functor {
        template <class T>
        void operator()(T& value) const {
            value += T(1);
        }
    };

    // 纯+号仿函数
    struct plus_functor {
        template <class T>
        void operator()(T& value) const {
            value = value + T(1);
        }
    };
};

template <class T>
void inc(T& value) {
    using step0_t = detail::plus_functor;
    using step1_t = typename boost::conditional<
        boost::has_plus_assign<T>::value,
        detail::plus_assignable_functor,
        step0_t
    >::type;
    using step2_t = typename boost::conditional<
        boost::has_post_increment<T>::value,
        detail::post_inc_functor,
        step1_t
    >::type;
    using step3_t = typename boost::conditional<
        boost::has_pre_increment<T>::value,
        detail::pre_inc_functor,
        step2_t
    >::type;

    step3_t()(value);
}

// 仅仅只有后置递增运算符的对象
struct has_only_postinc {
    has_only_postinc operator ++(int) {
        return *this;
    }
};

struct has_only_plus {
    explicit has_only_plus(int) {}
};

has_only_plus operator+ (has_only_plus v1, has_only_plus) {
    return v1;
} 

template <class T>
void inc_mpl(T& value) {
    using step0_t = detail::plus_functor;
    using step1_t = typename boost::mpl::if_<
        boost::has_plus_assign<T>,
        detail::plus_assignable_functor,
        step0_t
    >::type;
    using step2_t = typename boost::mpl::if_<
        boost::has_post_increment<T>,
        detail::post_inc_functor,
        step1_t
    >::type;
    using step3_t = typename boost::mpl::if_<
        boost::has_pre_increment<T>,
        detail::pre_inc_functor,
        step2_t
    >::type;
    step3_t()(value);
}

int main(int argc, char* argv[]) {
    int i = 0;
    inc(i);
    assert(i == 1);

    has_only_postinc pi;
    inc(pi);

    has_only_plus v(0);
    inc(v);

    inc_mpl(i);
    assert(i == 2);
    inc_mpl(pi);
    inc_mpl(v);
}


