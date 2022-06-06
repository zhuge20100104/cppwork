#ifndef _SYNC_QUEUE_HPP_
#define _SYNC_QUEUE_HPP_

#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>

using namespace std;

template <typename T> 
class SyncQueue {
    public:
        
        SyncQueue(int maxSize): m_maxSize(maxSize), m_needStop(false) {}

        void Put(const T& x) {
            Add(x);
        }

        void Put(T&& x) {
            Add(std::forward<T>(x));
        }
        
        void Take(std::list<T>& list) {
            std::unique_lock<std::mutex> locker(m_mutex);
            m_NotEmpty.wait(locker, [this] {
                        return m_needStop || NotEmpty();
                    });

            if(m_needStop) {
                return;
            }

            list = std::move(m_queue);
            m_NotFull.notify_one();
        }


        void Take(T& t) {
            std::unique_lock<std::mutex> locker(m_mutex);
            m_NotEmpty.wait(locker, [this] {
                        return m_needStop || NotEmpty();
                    });
            
            if(m_needStop) {
                return;
            }

            t = m_queue.front();
            m_queue.pop_front();
            m_NotFull.notify_one();
        }

        void Stop() {
            {
                std::lock_guard<std::mutex> locker(m_mutex);
                m_needStop = true;
            }

            m_NotFull.notify_all();
            m_NotEmpty.notify_all();
        }
        
        bool Empty() {
            std::lock_guard<std::mutex> locker;
            return m_queue.empty();
        }

        bool Full() {
            std::lock_guard<std::mutex> locker;
            return m_queue.size() == m_maxSize;
        }
    
    private:
        
        // 判断队列未满，内部使用的无锁版，否则会发生死锁
        bool NotFull() const {
            bool full = m_queue.size() >= m_maxSize;
            if(full) {
                std::cerr << "full, waiting, thread_id: " << std::this_thread::get_id() << std::endl;
            }
            return !full;
        }

        bool NotEmpty() const {
            bool empty = m_queue.empty();
            if(empty) {
                std::cerr << "empty, waiting, thread_id: " << std::this_thread::get_id() << std::endl;
            }
            return !empty;
        }

        template <typename F> 
        void Add(F&& x) {
            std::unique_lock<std::mutex> locker(m_mutex);
            m_NotFull.wait(locker, [this]{ return m_needStop || NotFull(); });
            
            if(m_needStop) {
                return;
            }

            m_queue.push_back(std::forward<F>(x));
            m_NotEmpty.notify_one();
        }

    private:
        std::list<T> m_queue; // 缓冲区
        std::mutex m_mutex; // 互斥量和条件变量结合起来使用
        std::condition_variable m_NotEmpty; // 不为空的条件变量
        std::condition_variable m_NotFull; // 不为满的条件变量
        int m_maxSize; // 同步队列的最大大小
        bool m_needStop; // 停止标志
};
#endif
