#ifndef _CHAPTOR06_06_TASKS_PROCESSOR_BASE_HPP_
#define _CHAPTOR06_06_TASKS_PROCESSOR_BASE_HPP_

#include <boost/noncopyable.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio/io_service.hpp>

#include <iostream>

namespace detail {
    // 封装task,避免异常发生中断执行
    template <class T>
    struct task_wrapped {
        private:
            T task_unwrapped_;
        
        public:
            explicit task_wrapped(const T& task_unwrapped):
                task_unwrapped_(task_unwrapped) {}
            
            void operator()() const {
                // 重置中断点
                try {
                    boost::this_thread::interruption_point();
                } catch(const boost::thread_interrupted&) {

                }

                try {
                    // 执行任务
                    task_unwrapped_();
                } catch(const std::exception& ex) {
                    std::cerr << "Exception: " << ex.what() << '\n';
                } catch(const boost::thread_interrupted&) {
                    std::cerr << "Thread interrupted\n";
                } catch(...) {
                    std::cerr << "Unknown exception\n";
                }
            }
    };

    template <class T>
    inline task_wrapped<T> make_task_wrapped(const T& task_unwrapped) {
        return task_wrapped<T>(task_unwrapped);
    }
};

namespace tp_base {
    class tasks_processor: private boost::noncopyable {
        protected:
            boost::asio::io_service ios_;
            boost::asio::io_service::work work_;

            tasks_processor():
                ios_(),
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
};
#endif