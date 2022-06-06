#ifndef _FREDRIC_ACCUM_TRAITS3_HPP_
#define _FREDRIC_ACCUM_TRAITS3_HPP_

// 声明一个traits模板
template <typename T>
class accumulation_traits;

#define MAKE_TRAITS(source_type, dest_type, zero_value) \
    template <>  \
    class accumulation_traits<source_type> { \
        public: \
            using AccT = dest_type; \
            static AccT const zero = zero_value; \
    }; \

MAKE_TRAITS(char, int, 0)
MAKE_TRAITS(short, int, 0)
MAKE_TRAITS(int, long, 0)

#undef MAKE_TRAITS

#endif