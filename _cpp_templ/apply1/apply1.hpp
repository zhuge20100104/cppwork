#ifndef _FREDRIC_APPLY_1_HPP_
#define _FREDRIC_APPLY_1_HPP_

template <typename T>
void apply(T& arg, void (*func)(T&)) {
    func(arg);
}

#endif