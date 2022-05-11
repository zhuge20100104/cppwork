#include <boost/atomic.hpp>
#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/thread.hpp>

#include <vector>
#include <deque>
#include <iostream>

#include <cassert>
// 未加工的数据包
struct data_packet {
    unsigned int value;
}; 

// 解码后的数据包
struct decoded_data {
    unsigned int value;
};

// 压缩后的数据包
struct compressed_data {
    unsigned int value;
};

using atomic_t = boost::atomic<unsigned int>;

class subsystem1 {
    atomic_t i_;

public:
    subsystem1(): i_(0) {}

    // 获取原始数据包
    data_packet get_data() {
        data_packet ret = { ++ i_};
        return ret;
    }
    
    // 最多运行10000次
    static const unsigned int max_runs = 10000;
    

    // 最多运行10000次
    bool is_stopped() const {
        return i_ == max_runs;
    } 
};

class subsystem2 {
    atomic_t i_;

public:
    subsystem2(): i_(0) {}

    void send_data(const compressed_data& data) {
        ++ i_;
        assert(data.value == i_);
    }

    unsigned int send_packets_count() const {
        return i_;
    }
};

// 解码数据
decoded_data decode_data(const data_packet& packet) {
    static unsigned int i = 0;
    ++ i;
    decoded_data ret = { packet.value };
    assert(i==packet.value);
    return ret;
}

// 压缩数据
compressed_data compress_data(const decoded_data& packet) {
    static unsigned int i = 0;
    ++ i;
    compressed_data ret = {packet.value};
    assert(i == packet.value);
    return ret;
}

class work_queue {
public:
    using task_type = boost::function<void()>;

private:
    std::deque<task_type> tasks_;
    boost::mutex mutex_;
    boost::condition_variable cond_;
    bool is_stopped_;

public:
    work_queue(): is_stopped_(false){}
    // 停止队列输入和输出
    void stop() {
        boost::lock_guard<boost::mutex> lock(mutex_);
        is_stopped_ = true;
        cond_.notify_all();
    }

    // 向任务队列中push任务
    void push_task(const task_type& task) {
        boost::unique_lock<boost::mutex> lock(mutex_);
        if(is_stopped_) {
            return;
        }

        tasks_.push_back(task);
        lock.unlock();
        cond_.notify_one();
    } 

    task_type pop_task() {
        boost::unique_lock<boost::mutex> lock(mutex_);
        while(tasks_.empty()) {
            if(is_stopped_) {
                return task_type();
            }
            cond_.wait(lock);
        }

        task_type ret = tasks_.front();
        tasks_.pop_front();
        return ret;
    }
};


work_queue decoding_queue, compressing_queue, sending_queue;
subsystem1 subs1;
subsystem2 subs2;

void do_decode(const data_packet& packet);
void start_data_accepting() {
    while(!subs1.is_stopped()) {
        data_packet packet = subs1.get_data();
        decoding_queue.push_task([packet](){
            do_decode(packet);
        });
    }
}

void do_compress(const decoded_data& packet);
void do_decode(const data_packet& packet) {
    decoded_data dec_packet = decode_data(packet);
    compressing_queue.push_task([dec_packet](){
        do_compress(dec_packet);
    });
}

void do_compress(const decoded_data& packet) {
    compressed_data com_packet = compress_data(packet);
    sending_queue.push_task([com_packet]() {
        subs2.send_data(com_packet);
    });
}

void run_while_not_stopped(work_queue& w_queue) {
    work_queue::task_type task;
    while(task = w_queue.pop_task()) {
        task();
    }
}

int main(int argc, char* argv[]) {
    boost::thread t_data_accepting(&start_data_accepting);
    boost::thread t_data_decoding([](){
        run_while_not_stopped(decoding_queue);
    });
    boost::thread t_data_compressing([](){
        run_while_not_stopped(compressing_queue);
    });
    boost::thread t_data_sending([](){
        run_while_not_stopped(sending_queue);
    });

    t_data_accepting.join();

    decoding_queue.stop();
    t_data_decoding.join();

    compressing_queue.stop();
    t_data_compressing.join();

    sending_queue.stop();
    t_data_sending.join();

    std::cerr << subs2.send_packets_count() << std::endl;
    assert(subs2.send_packets_count() == subsystem1::max_runs);
}
