#ifndef _THREAD_POOL_HPP_
#define _THREAD_POOL_HPP_
#include "sync_queue.hpp"

#include <list>
#include <thread>
#include <functional>
#include <memory>
#include <atomic>

// 定义同步队列中最大的任务数
const int MaxTaskCount = 100;

class ThreadPool {
    public:
        using Task = std::function<void()>;

        ThreadPool(int numThreads=std::thread::hardware_concurrency()): m_queue(MaxTaskCount) {
            Start(numThreads);
        }

        ~ThreadPool() {
            Stop();
        }
        
        // 析构函数中停止所有线程组中线程的函数
        void Stop() {
            // 保证多线程环境下只调用一次StopThreadGroup
            std::call_once(m_flag, [this]{ StopThreadGroup();  });
        }

        void AddTask(Task&& task) {
            m_queue.Put(std::forward<Task>(task));
        }

        void AddTask(const Task& task) {
            m_queue.Put(task);
        }



    private:
        
        void Start(int numThreads) {
            m_running = true;

            for(int i=0; i<numThreads; ++i) {
                m_threadgroup.push_back(std::make_shared<std::thread>(&ThreadPool::RunInThread, this));
            }
        }
        
        // 真正执行Task的函数
        void RunInThread() {
            while(m_running) {
                // 取任务并执行
                std::list<Task> list;
                m_queue.Take(list);

                for(auto& task: list) {
                    if(!m_running) {
                        return;
                    }

                    task();
                }
            }
        }

        void StopThreadGroup() {
            m_queue.Stop(); // 让同步队列中的线程停止
            m_running = false;   // 置为false,让内部线程跳出循环并退出

            for(auto& thread: m_threadgroup) {
                if(thread) {
                    thread->join(); 
                }
            }

            m_threadgroup.clear();
        }


        std::list<std::shared_ptr<std::thread> > m_threadgroup; // 处理任务的线程组
        SyncQueue<Task> m_queue;   // 同步队列
        std::atomic_bool m_running; // 是否停止的标志
        std::once_flag m_flag;     
};

#endif
