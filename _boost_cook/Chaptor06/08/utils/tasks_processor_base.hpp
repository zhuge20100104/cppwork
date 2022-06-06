#ifndef _CHAPTER06_08_TASKS_PROCESSOR_HPP_
#define _CHAPTER06_08_TASKS_PROCESSOR_HPP_
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
                // 重置中断点
                try {
                    boost::this_thread::interruption_point();
                } catch(const boost::thread_interrupted&) {

                }

                try {
                    task_unwrapped_();
                    // boost大部分的异常均继承自std::exception类，所以
                    // 直接catch std::exception即可
                } catch(const std::exception& e) {  
                    std::cerr << "Exception: " << e.what() << "\n";
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
}; // namespace detail

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
            // 获取单例的tasks_processor对象的静态方法
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
}; // namespace tp_base

#endif