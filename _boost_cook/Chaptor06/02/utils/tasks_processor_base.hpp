#ifndef _CHAPTOR06_02_TASKS_PROCESSOR_BASE_HPP_
#define _CHAPTOR06_02_TASKS_PROCESSOR_BASE_HPP_
#include <boost/noncopyable.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio/io_service.hpp>

#include <iostream>

namespace detail {
    template <class T>
    struct task_wrapped {
        private:
            T task_unwrapped_;
    
        public:
            explicit task_wrapped(const T& task_unwrapped): task_unwrapped_(task_unwrapped) {}

            void operator()() const {
                // 设置中断点，线程会在中断点退出
                try {
                    boost::this_thread::interruption_point();
                } catch (const boost::thread_interrupted&) {}

                try {
                    // 执行task
                    task_unwrapped_();
                } catch (const std::exception& e) {
                    std::cerr << "Exception: " << e.what() << '\n';
                } catch (const boost::thread_interrupted&) {
                    std::cerr << "Thread Interrupted...\n"; 
                } catch(...) {
                    std::cerr << "Unknown exception...\n";
                }
            }
    };

    template <class T>
    inline task_wrapped<T> make_task_wrapped(const T& task_unwrapped) {
        return task_wrapped<T>(task_unwrapped);
    }
}; // namespace detail

namespace tp_base {
    class tasks_processor: private boost::noncopyable {
        protected:
            boost::asio::io_service ios_;
            boost::asio::io_service::work work_;
        
            tasks_processor(): ios_(),
                work_(ios_) 
            {}

        public:
            static tasks_processor& get();

            template <class T>
            inline void push_task(const T& task_unwrapped) {
                ios_.post(detail::make_task_wrapped(task_unwrapped));
            }

            void start() {
                ios_.run();
            }

            void stop() {
                ios_.stop();
            }
    };

    tasks_processor& tasks_processor::get() {
        static tasks_processor proc;
        return proc;
    }
}; // namespace tp_base


#endif