#ifndef _FREDRIC_LOOP2_HPP_
#define _FREDRIC_LOOP2_HPP_

template <int Dim, typename T>
class DotProduct {
    public:
        static T result(T* a, T* b) {
            return *a * *b + DotProduct<Dim-1, T>::result(a+1, b+1); 
        }
};


template <typename T>
class DotProduct<1, T> {
    public:
        static T result(T* a, T* b) {
            return *a * *b;
        }
};

template <int Dim, typename T>
inline T dot_product(T* a, T* b) {
    return DotProduct<Dim, T>::result(a, b);
}

#endif