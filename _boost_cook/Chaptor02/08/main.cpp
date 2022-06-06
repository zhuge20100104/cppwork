#include <boost/type_traits/remove_pointer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_set.hpp>
#include <boost/ptr_container/clone_allocator.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <algorithm>
#include <set>
#include <cassert>

template <class T>
struct ptr_cmp: public std::binary_function<T, T, bool> {
    template<class T1>
    bool operator()(const T1& v1, const T1& v2) const {
        return operator()(*v1, *v2);
    }

    bool operator()(const T& v1, const T& v2) const {
        return std::less<T>()(v1, v2);
    }
};

template <class T>
struct ptr_deleter: public std::unary_function<T, void> {
    void operator()(T* ptr) {
        delete ptr;
    }
};

void example1() {
    std::set<int*, ptr_cmp<int> > s;
    s.insert(new int(1));
    s.insert(new int(0));
    // 验证set按顺序排序了
    assert(**s.begin() == 0);
    std::for_each(s.begin(), s.end(), ptr_deleter<int>());
}

void example2_b() {
    using int_uptr_t = std::unique_ptr<int>;
    std::set<int_uptr_t, ptr_cmp<int> > s;
    s.insert(int_uptr_t(new int(1)));
    s.insert(int_uptr_t(new int(0)));
    assert(**s.begin() == 0);
}

void example3() {
    using int_sptr_t = boost::shared_ptr<int>;
    std::set<int_sptr_t, ptr_cmp<int> > s;
    s.insert(int_sptr_t(new int(1)));
    s.insert(int_sptr_t(new int(0)));
    assert(**s.begin() == 0);
}

void correct_impl() {
    boost::ptr_set<int> s;
    s.insert(new int(1));
    s.insert(new int(0));
    assert(*s.begin() == 0);
}

void theres_more_example() {
    boost::ptr_vector<int> v;
    int value = 100;
    v.resize(10, &value);
    assert(v.size() == 10);
    assert(v.back() == 100);
}

int main(int argc, char* argv[]) {
    example1();
    example2_b();
    example3();
    correct_impl();
    theres_more_example();
}



