#ifndef _OPTIONAL_HPP_
#define _OPTIONAL_HPP_

#include <type_traits>
#include <functional>

template <typename T>
class Optional {
    using data_t = typename std::aligned_storage<sizeof(T), std::alignment_of<T>::value>::type;

    public:
        Optional() {}
        Optional(const T& v) {
            Create(v);
        }
        
        Optional(T&& v) { 
            Create(std::move(v));
        }

        ~Optional() {
            Destroy();
        }

        Optional(const Optional& other) {
            if(other.IsInit()) {
                Assign(other);
            }            
        }

        Optional(Optional&& other) {
            if(other.IsInit()) {
                Assign(std::move(other));
                other.Destroy();
            }
        }

        Optional& operator=(Optional&& other) {
            Assign(std::move(other));
            return *this;
        }

        Optional& operator=(const Optional& other) {
            Assign(other);
            return *this;
        }

        template <class ... Args> 
        void emplace(Args && ... args) {
            Destroy();
            Create(std::forward<Args>(args)...);
        }

        explicit operator bool() const {
            return IsInit();
        }

        T& operator*() {
            return *((T*)(&m_data));
        }

        T const& operator*() const {
            if(IsInit()) {
                return *((T*)(&m_data));
            }
            throw std::exception("解引用失败!");
        }

        bool operator == (const Optional<T>& rhs) const {
            // 1. 两个对象的初始化状态不等， return false
            // 2. 如果初始化状态相等，当前对象没有被初始化，说明两个对象都没有被初始化，那相等，return true
            // 3. 状态相等，且都被初始化了，比较Optional对象指向的值
            return (!bool(*this)) != (!rhs) ? false: (!bool(*this)) ? true: (*(*this)) == (*rhs); 
        }

        bool operator < (const Optional<T>& rhs) const {
            // 1. 如果右值没有初始化， 不可能小于空值，return false
            // 2. 如果右值不为空，左值为空，肯定小于 return true
            // 3. 左值，右值都不为空，比较值
            return !rhs ? false: (!(bool(*this))) ? true: ((*(*this)) < (*rhs));
        }

        bool operator != (const Optional<T>& rhs) const {
            return !(*this == (rhs));
        }

        bool IsInit() const {
            return m_hasInit;
        }
       

    private:
        template <typename... Args>
        void Create(Args&&... args) {
            new (&m_data) T(std::forward<Args>(args)...);
            m_hasInit = true;
        } 

        void Destroy() {
            if(m_hasInit) {
                m_hasInit = false;
                // 调用T的析构函数释放资源
                ((T*)(&m_data))->~T();
            }
        }

        void Assign(const Optional& other) {
            if(other.IsInit()) {
                Copy(other.m_data);
                m_hasInit = true;
            }else {
                Destroy();
            }
        }

        void Assign(Optional&& other) {
            if(other.IsInit()) {
                Move(std::move(other.m_data));
                m_hasInit = true;
                other.Destroy();
            } else {
                Destroy();
            }
        }

        // 调用移动构造函数移动构造
        void Move(data_t&& val) {
            Destroy();
            new (&m_data) T(std::move(*((T*)(&val))));
        } 

        void Copy(const data_t& val) {
            Destroy();
            // 直接释放调对象后在原址上用引用值重新分配，会产生拷贝
            new (&m_data) T(*((T*)(&val)));
        }



    private:
        bool m_hasInit = false;
        data_t m_data;
};
#endif 
