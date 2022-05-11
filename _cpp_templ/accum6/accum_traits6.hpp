#ifndef _FREDRIC_ACCUM_TRAITS6_HPP_
#define _FREDRIC_ACCUM_TRAITS6_HPP_

template <typename T>
class accumulation_traits;

#define MK_TRAITS(source_type, dest_type, zero_value) \
template <> \
class accumulation_traits<source_type> { \
    public:  \
        using AccT = dest_type;     \
        static AccT zero() {    \
            return zero_value;  \
        }                       \
};              \

MK_TRAITS(char, int, 0)
MK_TRAITS(short, int, 0)
MK_TRAITS(int, long, 0)
MK_TRAITS(unsigned int, unsigned long, 0)
MK_TRAITS(float, double, 0)

#undef MK_TRAITS

#endif