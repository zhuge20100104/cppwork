#ifndef _FREDRIC_COUNT_PTR_HPP_
#define _FREDRIC_COUNT_PTR_HPP_

#include "simplerefcount.hpp"
#include "stdobjpolicy.hpp"


template <typename T,
          typename CountPolicy = SimpleReferenceCount,
          typename ObjectPolicy = StandardObjectPolicy>
class CountingPtr: private CountPolicy, private ObjectPolicy {
    private:
        using CP = CountPolicy;
        using OP = ObjectPolicy;

        T* object_pointed_to;

    public:
        CountingPtr() {
            this->object_pointed_to = nullptr;
        }

        explicit CountingPtr(T* p) {
            this->init(p);   
        }

        CountingPtr(CountingPtr<T, CP, OP> const& cp):
            CP((CP const&)cp),
            OP((OP const&)cp) {
                this->attach(cp);
        }

        ~CountingPtr() {
            this->detach();
        }

        CountingPtr<T, CP, OP>& operator=(T* p) {
            assert(p != this->object_pointed_to);
            this->detach();

            this->init(p);
            return *this;
        }

        CountingPtr<T, CP, OP>& operator=(CountingPtr<T, CP, OP> const& cp) { 
            if(this->object_pointed_to != cp.object_pointed_to) {
                this->detach();

                CP::operator=((CP const&)cp);
                OP::operator=((OP const&)cp);
                this->attach(cp);
            }
            return *this;
        }

        T* operator->() const {
            return this->object_pointed_to;
        }

        T& operator*() const {
            return *this->object_pointed_to;
        }

        T* get() const {
            return this->object_pointed_to;
        }
    
    private:
        void init(T* p) {
            if(p!=nullptr) {
                CountPolicy::init(p);
            }
            this->object_pointed_to = p;
        }

        // 拷贝指针并增加引用计数
        void attach(CountingPtr<T, CP, OP> const& cp) {
            this->object_pointed_to = cp.object_pointed_to;
            if(cp.object_pointed_to != nullptr) {
                CountPolicy::increment(cp.object_pointed_to);
            }
        }

        // 减少引用计数，并销毁引用计数和对象，如果是最后一个持有引用计数的对象
        void detach() {
            if(this->object_pointed_to != nullptr) {
                CountPolicy::decrement(this->object_pointed_to);
                if(CountPolicy::is_zero(this->object_pointed_to)) {
                    // 销毁counter
                    CountPolicy::dispose(this->object_pointed_to);
                    // 销毁指向的对象
                    ObjectPolicy::dispose(this->object_pointed_to);
                }
            }
        }

};

#endif