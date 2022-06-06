#ifndef _FREDRIC_SIZE_OF__HPP_
#define _FREDRIC_SIZE_OF__HPP_

#include <cstddef>

template <typename T>
class type_size {
    public:
        static std::size_t const value = sizeof(T);
};
#endif