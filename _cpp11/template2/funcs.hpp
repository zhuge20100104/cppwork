#ifndef _FREDRIC_FUNCS_HPP_
#define _FREDRIC_FUNCS_HPP_
#include <map>
#include <memory>
#include <iostream>
#include <string>

#include <string.h>

template <typename T> 
T Add(T a, T b) {
    return a + b;
} 

template <typename T, int arrSize>
void ArraySum(T (&pArr) [arrSize], T& res) {
    for(int i=0; i<arrSize; ++i) {
        res += pArr[i];
    }
}

template <typename T, int arrSize>
T Max(T (&pArr)[arrSize]) {
    T maxEle {pArr[0]};
    for(int i=1; i<arrSize; ++i) {
        if(pArr[i]>maxEle) {
            maxEle = pArr[i];
        }
    }
    return maxEle;
}

template<typename T, int arrSize>
std::pair<T, T> MinMax(T (&pArr)[arrSize]) {
    std::pair<T, T> ret;
    T min{pArr[0]};
    T max{pArr[0]}; 
    for(int i=1; i<arrSize; ++i) {
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

template <int arrSize>
void  ArraySum(char* (&pArr) [arrSize], char* res) {
    for(int i=0; i<arrSize; ++i) {
        strcat(res, pArr[i]);
    }
}


template <int arrSize>
const char* Max(const char* (&pArr)[arrSize]) {
    const char* maxEle {pArr[0]};
    for(int i=1; i<arrSize; ++i) {
        if(strcmp(pArr[i], maxEle) > 0) {
            maxEle = pArr[i];
        }
    }
    return maxEle;
}


template<int arrSize>
std::pair<const char*, const char*> MinMax(const char* (&pArr)[arrSize]) {
    std::pair<const char*, const char*> ret;
    const char* min{pArr[0]};
    const char* max{pArr[0]}; 
    for(int i=0; i<arrSize; ++i) {
        if(strcmp(pArr[i], min) <0) {
            min = pArr[i];
        }
        if(strcmp(pArr[i], max)>0) {
            max = pArr[i];
        }
    }

    ret.first = min;
    ret.second = max;
    return std::move(ret);
}



template <int arrSize>
void  ArraySum(std::string (&pArr) [arrSize], std::string& res) {
    for(int i=0; i<arrSize; ++i) {
        res += pArr[i];
    }
}


template <int arrSize>
std::string Max(std::string (&pArr)[arrSize]) {
    std::string maxEle {pArr[0]};
    for(int i=1; i<arrSize; ++i) {
        if(pArr[i].compare(maxEle)> 0) {
            maxEle = pArr[i];
        }
    }
    return maxEle;
}


template<int arrSize>
std::pair<std::string, std::string> MinMax(std::string (&pArr)[arrSize]) {
    std::pair<std::string, std::string> ret;
    std::string min{pArr[0]};
    std::string max{pArr[0]}; 
    for(int i=0; i<arrSize; ++i) {
        if(pArr[i].compare(min) <0) {
            min = pArr[i];
        }
        if(pArr[i].compare(max)>0) {
            max = pArr[i];
        }
    }

    ret.first = min;
    ret.second = max;
    return std::move(ret);
}
#endif
