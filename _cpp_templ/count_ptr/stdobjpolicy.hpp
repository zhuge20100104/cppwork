#ifndef _FREDRIC_STD_OBJ_POLICY_HPP_
#define _FREDRIC_STD_OBJ_POLICY_HPP_

// 标准对象销毁器
class StandardObjectPolicy {
    public:
        template <typename T>
        void dispose(T* object) {
            delete object;
        }
};

#endif