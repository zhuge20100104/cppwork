#ifndef _FREDRIC_LOOP1_HPP_
#define _FREDRIC_LOOP1_HPP_

template <typename T>
inline T dot_product(int dim, T* a, T* b) {
    T res = T();

    for(int i=0; i<dim; ++i) {
        res += a[i] * b[i];
    }

    return res;
}

#endif