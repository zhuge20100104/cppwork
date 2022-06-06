#ifndef _FREDRIC_OBJECT_COUNTER_HPP_
#define _FREDRIC_OBJECT_COUNTER_HPP_

#include <cstddef>

template <typename CountedType>
class ObjectCounter {
    private:
        // 存在的对象个数
        static std::size_t count;
    
    protected:
        ObjectCounter() {
            ++count;
        }

        ObjectCounter(ObjectCounter<CountedType> const&) {
            ++count;
        }

        ~ObjectCounter() {
            --count;
        }

    public:
        static std::size_t live() {
            return count;
        }
}; 

template <typename CountedType>
std::size_t ObjectCounter<CountedType>::count = 0;

#endif