#ifndef _FREDRIC_OBJ_CREATES_HPP_
#define _FREDRIC_OBJ_CREATES_HPP_
#include <memory>

template <typename T, typename ... Params>
std::shared_ptr<T> CreateObject(Params && ... args) {
    std::shared_ptr<T> obj {new T(std::forward<Params>(args)...)};
    return std::move(obj);
}
#endif