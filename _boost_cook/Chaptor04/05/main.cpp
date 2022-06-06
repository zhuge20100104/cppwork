#include <boost/static_assert.hpp>
#include <boost/type_traits/is_pod.hpp>

#include <boost/mpl/int.hpp>

#include <iostream>

namespace detail {
    // 通用实现
    template <class T, class Tag> 
    T process_impl(const T& val, Tag /*ignore*/) {
        BOOST_STATIC_ASSERT(sizeof(val) != 1
            && sizeof(val) != 4
            && sizeof(val) != 8
        );
	std::cout << "通用版本被调用" << std::endl;
        return val;
    }

    // 1字节 int优化版本
    template <class T>
    T process_impl(const T& val, boost::mpl::int_<1> /*ignore*/) {
        BOOST_STATIC_ASSERT(sizeof(val) == 1);
	std::cout << "1字节优化版本被调用" << std::endl;
        return val;
    } 

    // 4字节优化版本
    template <class T>
    T process_impl(const T& val, boost::mpl::int_<4> /*ignore*/) {
        BOOST_STATIC_ASSERT(sizeof(val) == 4);
	std::cout << "4字节优化版本被调用" << std::endl;
        return val;
    }

    // 8字节优化版本
    template <class T>
    T process_impl(const T& val, boost::mpl::int_<8> /*ignore*/) {
        BOOST_STATIC_ASSERT(sizeof(val) == 8);
	std::cout << "8字节优化版本被调用" << std::endl;
        return val;
    }
};

// 仅仅做简单的调用传递
template <class T>
T process(const T& val) {
    BOOST_STATIC_ASSERT((boost::is_pod<T>::value));
    return detail::process_impl(val, boost::mpl::int_<sizeof(T)>());
}

int main(int argc, char* argv[]) {
    std::cout
        << ' ' << process(int(0)) << std::endl;
    
    std::cout
        << ' ' << process(double(1)) << std::endl;

    std::cout  
	<< ' ' << process(float(2)) << std::endl;

    std::cout
        << ' ' << process(char(3)) << std::endl;

    std::cout
	 << ' ' << process(unsigned(4)) << std::endl;

    std::cout
	 << ' ' << process(short(5))<< std::endl;
}
