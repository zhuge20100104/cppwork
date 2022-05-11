#ifndef _FREDRIC_SARRAY2_HPP_
#define _FREDRIC_SARRAY2_HPP_

#include <cassert>
#include <cstddef>
#include <memory>

template <typename T>
class SArray {
   public:
    explicit SArray(std::size_t s)
        : storage(std::make_unique<T[]>(s)), storage_size(s) {}

    SArray(SArray const& orig)
        : storage(std::make_unique<T[]>(orig.size())),
          storage_size(orig.size()) {
        copy(orig);
    }

    SArray<T>& operator=(SArray<T> const& orig) {
        if (&orig != this) {
            copy(orig);
        }
        return *this;
    }

    T operator[](std::size_t idx) const { return storage[idx]; }

    T& operator[](std::size_t idx) { return storage[idx]; }

    std::size_t size() const { return storage_size; }

    SArray<T>& operator+=(SArray<T> const& a);
    SArray<T>& operator*=(SArray<T> const& a);
    SArray<T>& operator*=(T const& s);

   private:
    void copy(SArray<T> const& orig) {
        assert(size() == orig.size());
        for (std::size_t idx = 0; idx < size(); ++idx) {
            storage[idx] = orig.storage[idx];
        }
    }

    std::unique_ptr<T[]> storage;
    std::size_t storage_size;
};

#endif