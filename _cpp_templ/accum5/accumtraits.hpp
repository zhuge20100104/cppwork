#ifndef _FREDRIC_ACCMU_TRAITS5_HPP_
#define _FREDRIC_ACCMU_TRAITS5_HPP_

template <typename T>
class accumulation_traits;

#define MAKE_TRAITS(source_type, dest_type, zero_value) \
template <> \
class accumulation_traits<source_type> { \
    public:     \
        using AccT = dest_type;  \
        static AccT zero() {    \
            return zero_value;  \
        }   \
};  \

MAKE_TRAITS(char, int, 0)
MAKE_TRAITS(short, int, 0)
MAKE_TRAITS(int, long, 0)
MAKE_TRAITS(unsigned int, unsigned long, 0)
MAKE_TRAITS(float, double, 0)

#undef MAKE_TRAITS

#endif