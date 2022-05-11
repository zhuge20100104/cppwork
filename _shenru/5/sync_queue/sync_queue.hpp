#ifndef _SYNC_QUEUE_HPP_
#define _SYNC_QUEUE_HPP_
#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>
#include "scout.hpp"

template <typename T> 
class SyncQueue {

    private:
        // 队列缓冲区已满  
        bool isFull() const {
            return m_queue.size() == m_maxSize;
        }

        // 队列缓冲区为空
        bool isEmpty() const {
            return m_queue.empty();
        }

    public:
        SyncQueue(int maxSize): m_maxSize(maxSize) {}

        // 入队操作
        void Put(const T& x) {
            std::lock_guard<std::mutex> lock(m_mutex);

            while(isFull()) {
                scout << "缓冲区满了，需要等待..." << std::endl;
                m_notFull.wait(m_mutex);
            }
            m_queue.emplace_back(x);
            m_notEmpty.notify_one();
        }

        // 出队操作
        void Take(T& x) {
            std::lock_guard<std::mutex> lock(m_mutex);
            while(isEmpty()) {
                scout << "缓冲区为空了，需要等待..." << std::endl;
                m_notEmpty.wait(m_mutex); 
            }
            x = m_queue.front();
            m_queue.pop_front();
            m_notFull.notify_one();
        }
        
        // 带锁的Empty版本
        bool Empty() {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_queue.empty();
        }

        // 带锁的Full版本
        bool Full() {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_queue.size() == m_maxSize;
        }

        // 带锁的size版本
        int Size() {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_queue.size();
        }

        // 不带锁的size版本
        int Count() {
            return m_queue.size();
        }

    private:
        std::list<T> m_queue; // 队列缓冲区
        std::mutex m_mutex; // 互斥量和条件变量结合使用
        std::condition_variable_any m_notEmpty; // 不为空的条件变量
        std::condition_variable_any m_notFull; // 不为满的条件变量
        int m_maxSize;  // 同步队列的最大大小 

};

#endif