#ifndef _FREDRIC_FUNCS_HPP_
#define _FREDRIC_FUNCS_HPP_
#include <map>

template <typename T> 
T Add(T a, T b) {
    return a + b;
} 

template <typename T>
T ArraySum(T* pArr, int arrSize) {
    T ret{};
    for(int i=0; i<arrSize; ++i) {
        ret += pArr[i];
    }
    return ret;
}

template <typename T>
T Max(T* pArr, int arrSize) {
    T maxEle {pArr[0]};
    for(int i=1; i<arrSize; ++i) {
        if(pArr[i]>maxEle) {
            maxEle = pArr[i];
        }
    }
    return maxEle;
}

template<typename T>
std::pair<T, T> MinMax(T* pArr, int arrSize) {
    std::pair<T, T> ret;
    T min{pArr[0]};
    T max{pArr[0]}; 
    for(int i=0; i<arrSize; ++i) {
        if(pArr[i]<min) {
            min = pArr[i];
        }
        if(pArr[i]>max) {
            max = pArr[i];
        }
    }

    ret.first = min;
    ret.second = max;
    return std::move(ret);
}
#endif
