#ifndef _FREDRIC_ELEMENT_HPP_
#define _FREDRIC_ELEMENT_HPP_

#include <vector>
#include <list>
#include <stack>

template <typename T>
class ElementT;

#define MK_ELEMENT(container_type) \
    template <typename T> \
    class ElementT<container_type<T>> { \
        public: \
            using Type = T; \
    };  \

MK_ELEMENT(std::vector)
MK_ELEMENT(std::list)
MK_ELEMENT(std::stack)

#undef MK_ELEMENT

#endif