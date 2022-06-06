#ifndef _FREDRIC_POW3_HPP_
#define _FREDRIC_POW3_HPP_

// 通用递归模板，求3的N次方
template <int N>
class Pow3 {
    public:
        enum {result = 3 * Pow3<N-1>::result};
};

// 偏特化，递归终止条件
template <>
class Pow3<0> {
    public:
        enum {result = 1};
};



#endif 