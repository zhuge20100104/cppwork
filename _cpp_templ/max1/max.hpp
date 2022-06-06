#ifndef _FREDRIC_MAX1_HPP_
#define _FREDRIC_MAX1_HPP_

template <typename T>
inline T const& max(T const& a, T const& b) {
    return a < b? b: a;
}
#endif