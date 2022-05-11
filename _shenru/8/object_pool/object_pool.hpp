#include <string>
#include <functional>
#include <memory>
#include <map>
#include "noncopyable.hpp"
using std::string;
using std::shared_ptr;
using std::multimap;

const int MaxObjectNum = 10;

template <typename T>
class ObjectPool: public NonCopyable {
    template <typename ... Args>
    // 输入为Args类型，返回为std::shared_ptr<T>类型的函数
    using Constructor = std::function<shared_ptr<T>(Args...)>;
    public:

        // 初始化对象池
        template <typename ... Args> 
        void Init(size_t num, Args &&... args) {
            if(num <= 0 || num > MaxObjectNum) {
                throw std::logic_error("object num out of range");
            }

            auto constructorName = typeid(Constructor<Args...>).name();
            for(size_t i=0; i < num; ++i) {
                m_object_map.emplace(constructorName, shared_ptr<T>(new T(std::forward<Args>(args)...),
                    [this, constructorName] (T* p){  // 删除器中回收到对象池，供下次使用,删除时used_count-1，使用p构造一个新的，令used_count + 1
                        m_object_map.emplace(std::move(constructorName), shared_ptr<T>(p));                      
                    } ));
            }
        }

        // 从对象池中获取一个对象
        template <typename ... Args>
        shared_ptr<T> Get() {
            string constructName = typeid(Constructor<Args...>).name();
            auto range = m_object_map.equal_range(constructName);
            for(auto it = range.first; it != range.second; it++) {
                auto ptr = it->second;
                m_object_map.erase(it);
                return ptr;
            }
            return nullptr;
        }

    private:
        multimap<string, std::shared_ptr<T> > m_object_map;
};  