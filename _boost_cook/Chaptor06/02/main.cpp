#include "utils/tasks_processor_base.hpp"

#include <boost/exception_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <stdexcept>

using namespace tp_base;

// 前向声明
void func_test2();

void process_exception(const boost::exception_ptr& exec_ptr) {
    try {
        boost::rethrow_exception(exec_ptr);
    } catch(const boost::bad_lexical_cast& /*e*/) {
        std::cerr << "Lexical cast exception detected \n";
        tasks_processor::get().push_task(&func_test2);
    } catch(...) {
        std::cerr << "Can not handle such exceptions: \n"
            << boost::current_exception_diagnostic_information()
            << "\n";
        // 停止io_service::run
        tasks_processor::get().stop();
    }
}

void func_test1() {
    try {
        boost::lexical_cast<int>("oops!");
    } catch(...) {
        auto exec = boost::current_exception();
        tasks_processor::get().push_task([exec](){
            process_exception(exec);
        });
    }
}

void func_test2() {
    try {
        BOOST_THROW_EXCEPTION(std::logic_error("Some fatal logic error"));
    } catch(...) {  
        auto exec = boost::current_exception();
        tasks_processor::get().push_task([exec](){
            process_exception(exec);
        });
    }
}

void run_sub_thread_throw(boost::exception_ptr& ptr) {
    
    try {
        boost::lexical_cast<float>("not-a-float");
    } catch(...) {
        ptr = boost::current_exception();
    }
}

int main(int argc, char* argv[]) {
    tasks_processor::get().push_task(&func_test1);
    tasks_processor::get().start();

    boost::exception_ptr ptr;
    boost::thread t([&ptr](){
        run_sub_thread_throw(ptr);
    });
    t.join();

    // 子线程有异常，在主线程中抛出异常
    if(ptr) {
        std::cerr << "bad exception occurred in sub thread\n";
        boost::rethrow_exception(ptr);
    }
}


