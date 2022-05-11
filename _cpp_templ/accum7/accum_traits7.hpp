#ifndef _FREDRIC_ACCUM_TRAITS6_HPP_
#define _FREDRIC_ACCUM_TRAITS6_HPP_

template <typename T, int initial_value=0>
class accumulation_traits;

#define MK_TRAITS(source_type, dest_type) \
template <int initial_value> \
class accumulation_traits<source_type, initial_value> { \
    public:  \
        using AccT = dest_type;     \
        static AccT init() {    \
            return initial_value;  \
        }                       \
};              \


MK_TRAITS(char, int)
MK_TRAITS(short, int)
MK_TRAITS(int, long)
MK_TRAITS(unsigned int, unsigned long)
MK_TRAITS(float, double)

#undef MK_TRAITS

#endif