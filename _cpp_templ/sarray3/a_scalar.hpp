#ifndef _FREDRIC_A_SCALAR_HPP_
#define _FREDRIC_A_SCALAR_HPP_

#include <cstddef>

template <typename T>
class A_Scalar {
    private:
        T const& s;
    
    public:
        A_Scalar(T const& v): s(v) {}

        T operator[] (std::size_t idx) const {
            return s;
        }

        std::size_t size() const {
            return 0;
        }
};
#endif