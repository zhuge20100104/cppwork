#ifndef _OBSERVER_HPP_
#define _OBSERVER_HPP_

#include <iostream>
#include <string>
#include <functional>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::map;

#include "noncopyable.hpp"

template <typename Func>
class Events: NonCopyable {
    public:
        // 注册观察者，支持右值引用
        int Connect(Func&& f) {
            return Assign(f);
        }

        // 注册观察者，左值
        int Connect(const Func& f) {
            return Assign(f);
        }

        // 移除观察者
        void Disconnect(int key) {
            m_connections.erase(key);
        }

        // 通知所有观察者
        template <typename ... Args>
        void Notify(Args&& ... args) {
            for(auto &it : m_connections) {
                auto& func = it.second;
                func(std::forward<Args>(args)...);
            }
        }
    private:

        // 保存观察者并分配观察者编号
        template <typename F>
        int Assign(F&& f) {
            int k = m_observerId++;
            m_connections.emplace(k, std::forward<F>(f));
            return k;
        }

        int m_observerId = 0; //观察者对应编号
        map<int, Func> m_connections; // 观察者列表
};

#endif