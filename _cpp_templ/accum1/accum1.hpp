#ifndef _FREDRIC_ACCUM1_HPP_
#define _FREDRIC_ACCUM1_HPP_

template <typename T>
inline T accum(T const* beg, T const* end) {
    T total = T(); // 假定 T()可以做0值初始化
    while(beg != end) {
        total += *beg;
        ++beg;
    }
    return total;
}
#endif