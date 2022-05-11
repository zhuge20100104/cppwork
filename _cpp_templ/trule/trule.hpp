#ifndef _FREDRIC_TRULE_HPP_
#define _FREDRIC_TRULE_HPP_
// Trule 将所有权从 一个holder转移到另一个holder

template <typename T>
class Holder;

template <typename T> 
class Trule {
    private:
        T* ptr;
    
    public:
        // 通过Holder对象构造 Trule
        Trule(Holder<T>& h) {
            ptr = h.get();
            h.release();
        }

        // 拷贝构造，偷取另一个Trule对象的资源
        Trule(Trule<T> const& t) {
            ptr = t.ptr;
            const_cast<Trule<T> &>(t).ptr = nullptr;
        }

        ~Trule() {
            delete ptr;
            ptr = nullptr;
        }

        // 左值引用和赋值不允许
        Trule(Trule<T> &)=delete;
        Trule<T>& operator=(Trule<T>&)=delete;

        friend class Holder<T>;
};

#endif