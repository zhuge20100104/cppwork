#ifndef _FREDRIC_FUNCS_HPP_
#define _FREDRIC_FUNCS_HPP_

#include <map>

template <typename T>
struct Max
{
    T operator()(T x, T y) const {
        return x>y?x:y;
    }
};

template <typename T>
struct Greator
{
    bool operator()(T a, T b) const {
        return a > b;
    }
};

template <typename T>
struct Less {
    bool operator()(T a, T b) const {
        return a < b;
    }
};

template <typename T> 
struct MinMax {
    std::pair<T, T> operator()(T itBegin, T itEnd) const {
        std::pair<T, T> minMax {itBegin, itBegin};
        ++itBegin;
        while(itBegin != itEnd) {
            if(*itBegin < *minMax.first) {
                minMax.first = itBegin;
            }

            if(*itBegin > *minMax.second) {
                minMax.second = itBegin;
            }
            ++itBegin;
        }

        return std::move(minMax);
    }
};



#endif