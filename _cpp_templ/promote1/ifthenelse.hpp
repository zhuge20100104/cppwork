#ifndef _FREDRIC_IF_THEN_ELSE_HPP_
#define _FREDRIC_IF_THEN_ELSE_HPP_

// 总体模板
template <bool Bool, typename Ta, typename Tb>
class IfThenElse;

// 偏特化
template <typename Ta, typename Tb>
class IfThenElse<true, Ta, Tb> {
    public:
        using ResultT = Ta;
};

// false 偏特化
template <typename Ta, typename Tb>
class IfThenElse<false, Ta, Tb> {
    public:
        using ResultT = Tb;
};

#endif