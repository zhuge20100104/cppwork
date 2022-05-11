#ifndef _IOC_HPP_
#define _IOC_HPP_
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include <boost/any.hpp>
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>

class IocContainer: boost::noncopyable {
    public:
        IocContainer(void) {}
        ~IocContainer(void) {}
        
        // 其中Depend为依赖类对象，Args为依赖类对象的参数列表类型
        // T 为需要创建的对象
        // T 不是 Depend的父类，一般情况
        template <typename T, typename Depend, typename ... Args> 
        typename std::enable_if<!std::is_base_of<T,Depend>::value>::type RegisterType(const std::string& strKey) {
            std::function<T* (Args...)> function = [](Args ... args) {
                return new T(new Depend(args...));
            };
            RegisterType(strKey, function);
        }
        
        // T是Depend的父类
        // 允许直接创建Depend
        template <typename T, typename Depend, typename ... Args> 
        typename std::enable_if<std::is_base_of<T,Depend>::value>::type RegisterType(const std::string& strKey) {
            std::function<T* (Args...)> function = [](Args ... args) {
                return new Depend(args...);
            };
            RegisterType(strKey, function);
        }

        // 直接注册简单对象
        template <typename T, typename ... Args> 
        void RegisterSimple(const std::string& strKey) {
            std::function<T* (Args...)> function = [](Args ... args) {
                return new T(args...);
            };
            RegisterType(strKey, function);
        }
       

        template <typename T, typename ... Args>
        T* Resolve(const std::string& strKey, Args ... args) {
            // 没找到对应的构造函数，返回空指针
            if(m_creatorMap.find(strKey) == m_creatorMap.end()) {
                return nullptr;
            }

            boost::any resolver = m_creatorMap[strKey];
            try {
                std::function<T* (Args...)> function = boost::any_cast<std::function<T* (Args...)>>(resolver);
                return function(args...);
            }catch(boost::bad_any_cast& ex) {
                std::cerr << "参数个数或类型不对, err: ["<< ex.what() <<"]" << std::endl;
                throw std::invalid_argument("参数个数或类型不匹配!");
            }
        }   
    
        template<typename T, typename ... Args>
        std::shared_ptr<T> ResolveShared(const std::string& strKey, Args ... args){
            T* t = Resolve<T>(strKey, args...);
            return std::shared_ptr<T>(t);
        }

    private:
        
        void RegisterType(const std::string& strKey, boost::any constructor) {
            // 说明找到了strKey对应的对象，不能重复注册
            if(m_creatorMap.find(strKey) != m_creatorMap.end()) {
                throw std::invalid_argument("this key has already exist!");
            }

            // 通过boost::any擦除不同类型的构造器
            m_creatorMap.emplace(strKey, constructor);
        }
        std::unordered_map<std::string, boost::any> m_creatorMap;
};


#endif
