#ifndef _SIMPLE_SYNC_QUEUE_HPP_
#define _SIMPLE_SYNC_QUEUE_HPP_
#include <thread>
#include <condition_variable>
#include <mutex>
#include <list>
#include <iostream>

template <typename T> 
class SimpleSyncQueue {
    public:
        SimpleSyncQueue() {}
        
        void Put(const T& x) {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_queue.push_back(x);
            m_NotEmpty.notify_one();
        }

        void Take(T& x) {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_NotEmpty.wait(lock, [this]{return !m_queue.empty(); });
            x = m_queue.front();
            m_queue.pop_front();
        }

        // 带锁的Empty函数
        bool Empty() {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_queue.empty();
        }

        // 带锁的size函数
        size_t Size() {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_queue.size();
        }

    private:
        std::list<T> m_queue;
        std::mutex m_mutex;
        std::condition_variable m_NotEmpty;
};
#endif