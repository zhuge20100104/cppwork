#include <boost/function.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/condition_variable.hpp>

#include <deque>
#include <iostream>

// 工作队列
class work_queue {
public:
    using task_type = boost::function<void()>;

private:
    std::deque<task_type> tasks_;
    boost::mutex  tasks_mutex_;
    boost::condition_variable cond_;

public:
    void push_task(const task_type& task) {
        boost::unique_lock<boost::mutex> lock(tasks_mutex_);
        tasks_.push_back(task);
        lock.unlock();
        // 通知可以取任务了
        cond_.notify_one();
    }

    task_type try_pop_task() {
        task_type ret; 
        boost::lock_guard<boost::mutex> lock(tasks_mutex_);
        if(!tasks_.empty()) {
            ret = tasks_.front();
            tasks_.pop_front();
        }
        return ret;
    }

    task_type pop_task() {
        boost::unique_lock<boost::mutex> lock(tasks_mutex_);
        while(tasks_.empty()) {
            cond_.wait(lock);
        }
        task_type ret = tasks_.front();
        tasks_.pop_front();
        return ret;
    }

    void flush() {
        boost::lock_guard<boost::mutex> lock(tasks_mutex_);
        cond_.notify_all();
    }
};

// 全局的工作队列
work_queue g_queue;

void do_nothing() {
    std::cout << "do nothing" << std::endl;
}

const std::size_t tests_tasks_count = 3000;

void pusher() {
    for(std::size_t i=0; i<tests_tasks_count; ++i) {
        g_queue.push_task(&do_nothing);
    }
}

void pop_sync() {
    for(std::size_t i=0; i<tests_tasks_count; ++i) {
        g_queue.pop_task()();
    }
}

int main(int argc, char* argv[]) {
    boost::thread_group pop_group;
    boost::thread_group push_group;
    for(std::size_t i=0; i<3; ++i) {
        pop_group.create_thread(&pop_sync);
    }

    for(std::size_t i=0; i<3; ++i) {
        push_group.create_thread(&pusher);
    }

    push_group.join_all();
    g_queue.flush();
    pop_group.join_all();

    assert(!g_queue.try_pop_task());

    g_queue.push_task(&do_nothing);

    assert(g_queue.try_pop_task());
}