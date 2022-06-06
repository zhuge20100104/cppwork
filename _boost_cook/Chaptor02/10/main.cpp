#include <boost/noncopyable.hpp>
#include <boost/utility/base_from_member.hpp>

#include <sstream>
#include <iostream>

class tasks_processor: public boost::noncopyable {
    // 注意这里用的是一个引用，注意引用的生命周期管理
    std::ostream& log_;
protected:
    virtual void do_process() = 0;

public:
    explicit tasks_processor(std::ostream& log): log_(log) {
    }
    // process中调用虚函数 do_process
    void process() {
        log_ << "Starting data processing";
	log_ << std::endl;
        do_process();
    }
};

class fake_tasks_processor_fixed
    : boost::base_from_member<std::ostringstream>,
    public tasks_processor {
    using logger_t = boost::base_from_member<std::ostringstream>;
    
    virtual void do_process() {
        logger_t::member << "Fake processor processed!";
        std::cout << logger_t::member.str() << std::endl;
    }

public:
    // boost::base_from_member可以解决基类构造顺序的问题，先构造 logger_t
    // 再构造 tasks_processor
    fake_tasks_processor_fixed():
        logger_t(),
        tasks_processor(logger_t::member) {
    }
};

class fake_tasks_processor2:
    boost::base_from_member<std::ostringstream, 0>,
    boost::base_from_member<std::ostringstream, 1>,
    public tasks_processor {

    using logger0_t = boost::base_from_member<std::ostringstream, 0>;
    using logger1_t = boost::base_from_member<std::ostringstream, 1>;

    virtual void do_process() {
        logger0_t::member << "0: Fake processor2 processed!";
        logger1_t::member << "1: Fake processor2 processed!";
        std::cout << logger0_t::member.str() << std::endl;
        std::cout << logger1_t::member.str() << std::endl;
    }

public:
    fake_tasks_processor2():
        logger0_t(),
        logger1_t(),
        tasks_processor(logger0_t::member) {

    }
};

int main(int argc, char* argv[]) {
    fake_tasks_processor_fixed tp;
    tp.process();

    fake_tasks_processor2 tp2;
    tp2.process();
}





