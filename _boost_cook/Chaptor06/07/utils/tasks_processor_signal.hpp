#ifndef _CHAPTOR06_07_TASKS_PROCESSOR_SIGNALS_HPP_
#define _CHAPTOR06_07_TASKS_PROCESSOR_SIGNALS_HPP_

#include "tasks_processor_multithread.hpp"

#include <boost/asio/signal_set.hpp>
#include <boost/function.hpp>

namespace tp_full {

    class tasks_processor: public tp_multithread::tasks_processor {
        private:
            tasks_processor():
                tp_multithread::tasks_processor(),
                signals_(ios_)
             {}

            boost::asio::signal_set signals_;
            boost::function<void(int)> users_signal_handler_;

            void handle_signals(
                const boost::system::error_code& ec,
                int signal_number
            ) {
                if(ec) {
                    std::cerr << "Error in signal handling: " << ec << '\n';
                } {
                    // 处理当前signal事件
                    detail::make_task_wrapped([this, signal_number](){
                        this->users_signal_handler_(signal_number);
                    })  
                        ();
                }

                // 等待下一个signal
                signals_.async_wait([this](const boost::system::error_code& ec, int sign_number){
                    this->handle_signals(ec, sign_number);
                });
            }
        
        public:
            static tasks_processor& get();
            
            template <class Func> 
            void register_signals_handler(const Func& f,
                const std::vector<int>& signals_to_wait) {
                // 确认是首次注册
                assert(!users_signal_handler_);

                users_signal_handler_ = f;
                // 注册信号到信号集
                std::for_each(signals_to_wait.begin(),
                    signals_to_wait.end(),
                    [this](const int signal_num) {
                        this->signals_.add(signal_num);
                    });
                
                // 等待信号集中的信号发生，调用处理函数
                signals_.async_wait([this](
                    const boost::system::error_code& ec,
                    int signal_num
                ){
                    this->handle_signals(ec, signal_num);
                });
            }
    };

    tasks_processor& tasks_processor::get() {
        static tasks_processor proc;
        return proc;
    }
};

#endif
