#ifndef _SINGLETON_HPP_
#define _SINGLETON_HPP_
#include <memory>

template <typename T>
using shared_ptr = typename std::shared_ptr<T>;

template <typename T> 
class Singleton {
    public:
        template <typename ... Args> 
        static shared_ptr<T>&  Instance(Args&& ... args) {
            if(!m_pInstance) {
                m_pInstance = shared_ptr<T>(new T(std::forward<Args>(args)...));
            }
            return m_pInstance;
        }

    private:
        static shared_ptr<T> m_pInstance;
        Singleton() = delete;
        virtual ~Singleton() = delete;
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;
};

template <typename T>
shared_ptr<T> Singleton<T>::m_pInstance = nullptr;

#endif