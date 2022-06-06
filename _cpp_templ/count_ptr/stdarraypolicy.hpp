#ifndef _FREDRIC_STD_ARRAY_POLICY_HPP_
#define _FREDRIC_STD_ARRAY_POLICY_HPP_

// 标准对象销毁器
class StandardArrayPolicy {
    public:
        template <typename T>
        void dispose(T* array) {
            delete [] array;
        }
};

#endif