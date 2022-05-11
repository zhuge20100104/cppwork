#ifndef _CHAPTOR06_05_TASKS_PROCESSOR_MULTITHREAD_HPP_
#define _CHAPTOR06_05_TASKS_PROCESSOR_MULTITHREAD_HPP_

#include "tasks_processor_base.hpp"

namespace tp_multithread {

    
    class tasks_processor: public tp_base::tasks_processor {
        public:
            // 获取单例的tasks_processor对象的静态方法
            static tasks_processor& get();

            void start_multiple(std::size_t threads_count = 0) {
                if(!threads_count) {
                    threads_count = (std::max)(
                        static_cast<int>(boost::thread::hardware_concurrency()),
                        1
                    );
                }

                // 去除掉当前线程
                -- threads_count;
                boost::thread_group tg;
                for(std::size_t i=0; i<threads_count; ++i) {
                    tg.create_thread([this]() {
                        this->ios_.run();
                    });
                }

                ios_.run();
                tg.join_all();
            }
    };

    tasks_processor& tasks_processor::get() {
        static tasks_processor proc;
        return proc;
    }
};
#endif