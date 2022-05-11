#ifndef _FREDRIC_ACCUM_TRAITS2_HPP_
#define _FREDRIC_ACCUM_TRAITS2_HPP_

// 类模板声明
template <typename T>
class accumulation_traits;

#define MAKE_TRAITS(souce_type, acct_type) \
    template <> \
    class accumulation_traits<souce_type>{ \
    public: \
        using AccT = acct_type; \
    };  \

MAKE_TRAITS(char, int)
MAKE_TRAITS(short, int)
MAKE_TRAITS(int, long)
MAKE_TRAITS(unsigned int, unsigned long)
MAKE_TRAITS(float, double)

#undef MAKE_TRAITS 



#endif