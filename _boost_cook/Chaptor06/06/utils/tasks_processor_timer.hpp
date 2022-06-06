#ifndef _CHAPTOR06_06_TASKS_PROCESSOR_TIMER_HPP_
#define _CHAPTOR06_06_TASKS_PROCESSOR_TIMER_HPP_
// 给基础的tasks_processor_base加上timer功能

#include "tasks_processor_base.hpp"

#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/system/error_code.hpp>
#include <boost/make_shared.hpp>

#include <iostream>

namespace detail {
    using duration_type_t = boost::asio::deadline_timer::duration_type;

    template <class Functor>
    struct timer_task: public task_wrapped<Functor> {
        private:
            using base_t = task_wrapped<Functor>;
            boost::shared_ptr<boost::asio::deadline_timer> timer_;

        public:
            template <class Time>
            explicit timer_task(boost::asio::io_service& ios,
                const Time& duration_or_time,
                const Functor& task_unwrapped):
                    base_t(task_unwrapped),
                    timer_(boost::make_shared<boost::asio::deadline_timer>(
                        ios, duration_or_time
                        )) 
            {
           
            }

            void push_task() const {
                timer_->async_wait(*this);
            }

            void operator()(const boost::system::error_code& error) const {
                if(!error) {
                    base_t::operator()();
                } else {
                    std::cerr << error << '\n';
                }
            }
    };

    template <class Time, class Functor>
    inline timer_task<Functor> make_timer_task(
        boost::asio::io_service& ios,
        const Time& duration_or_time,
        const Functor& task_unwrapped
    ) {
        return timer_task<Functor>(ios, duration_or_time, task_unwrapped);
    }
}; // namespace detail

namespace tp_timers {
    class tasks_processor: public tp_base::tasks_processor {
        public:
            static tasks_processor& get();

            using duration_type_t = boost::asio::deadline_timer::duration_type;
            template <class Functor>
            void run_after(duration_type_t duration, const Functor& f) {
                detail::make_timer_task(ios_, duration, f).push_task();
            }

            using time_type_t = boost::asio::deadline_timer::time_type;
            template <class Functor>
            void run_at(time_type_t time, const Functor& f) {
                detail::make_timer_task(ios_, time, f).push_task();
            }
    };
}; // namespace tp_timers
#endif
