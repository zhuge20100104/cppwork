#ifndef _FREDRIC_TYPE1_HPP_
#define _FREDRIC_TYPE1_HPP_

template <typename T>
class IsFounda {
    public:
        enum {Yes = 0, No = 1};
};

#define MK_FOUNDA_TYPE(T) \
template <> \
class IsFounda<T> { \
    public: \
        enum {Yes = 1, No = 0}; \
}; \

MK_FOUNDA_TYPE(void)
MK_FOUNDA_TYPE(bool)
MK_FOUNDA_TYPE(char)
MK_FOUNDA_TYPE(signed char)
MK_FOUNDA_TYPE(unsigned char)
MK_FOUNDA_TYPE(wchar_t)

MK_FOUNDA_TYPE(signed short)
MK_FOUNDA_TYPE(unsigned short)
MK_FOUNDA_TYPE(signed int)
MK_FOUNDA_TYPE(unsigned int)
MK_FOUNDA_TYPE(signed long)
MK_FOUNDA_TYPE(unsigned long)

#if LONGLONG_EXISTS
    MK_FOUNDA_TYPE(signed long long)
    MK_FOUNDA_TYPE(unsigned long long)
#endif

MK_FOUNDA_TYPE(float)
MK_FOUNDA_TYPE(double)
MK_FOUNDA_TYPE(long double)

#undef MK_FOUNDA_TYPE

#endif 