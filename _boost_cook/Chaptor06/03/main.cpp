#include "utils/tasks_processor_base.hpp"

#include <boost/array.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/thread/thread.hpp>
#include <boost/atomic.hpp>

#include <cstddef>

using namespace tp_base;

static const std::size_t data_length = 10000;

struct vector_type: public boost::array<std::size_t, data_length> {
    void* alignment;
};

// array<array<std::size_t, 10000>, 4>
// 4 * 10000
using data_t = boost::array<vector_type, 4>;

void fill_data(vector_type& data);
void compute_send_data(data_t& data);

void runner(std::size_t thread_index, boost::barrier& data_barrier, data_t& data) {
    for(std::size_t i=0; i<1000; ++i) {
        fill_data(data.at(thread_index));

        data_barrier.wait();
        // 第一个线程会运行compute_send_data
        if(!thread_index) {
            compute_send_data(data);
        }
        // 其他线程在这里等 第一个线程汇合
        data_barrier.wait();
    }
}

void clever_implementation();

int main(int argc, char* argv[]) {
    // 初始化一个栅栏对象
    boost::barrier data_barrier(data_t::static_size);

    data_t data;

    boost::thread_group tg;

    for(std::size_t i=0; i<data_t::static_size; ++i) {
        tg.create_thread([i, &data_barrier, &data]() {
            runner(i, data_barrier, data);
        });
    }

    tg.join_all();

    clever_implementation();
}

using atomic_count_t = boost::atomic<unsigned int>;

void clever_runner(
    std::size_t thread_index, 
    std::size_t iteration,
    atomic_count_t& counter,
    data_t& data
) {
    fill_data(data.at(thread_index));

    // 说明四个线程中的最后一个做完了fill_data
    if(++counter == data_t::static_size) {
        // 发数据
        compute_send_data(data);
        // iteration只在某个线程里面更新，恰巧 counter=4那个最后完成的线程里面更新
        // 不存在多线程写入的情况，所以不必要是原子变量
        ++iteration;
        // 达到1000次迭代次数，结束
        if(iteration == 1000) { 
            tasks_processor::get().stop();
            return;
        }

        // 重置一下线程计数器个数，使用boost::barrier栅栏类不需要重置线程计数器个数
        // 因为boost::barrier类在m_count == 0时，会自动调用 fct_函数重置
        counter = 0;
        for(std::size_t i=0; i<data_t::static_size; ++i) {
            tasks_processor::get().push_task(
                [i, iteration, &counter, &data]() {
                    clever_runner(i, iteration, counter, data);
                }
            );
        }
    }
}

void clever_implementation() {
    atomic_count_t counter(0);

    data_t data;
    tasks_processor& tp = tasks_processor::get();
    for(std::size_t i=0; i<data_t::static_size; ++i) {
        tp.push_task([i, &counter, &data](){
            clever_runner(i, 0, counter, data);
        });
    }

    tp.start();
}

// 功能实现部分
// 这两个函数没什么意义，只是简单模拟而已
void fill_data(vector_type& data) {
    for(std::size_t i=0; i<vector_type::static_size; ++i) {
        data[i] = i;
    }
    data.alignment = nullptr;
}

void compute_send_data(data_t& data) {
    for(std::size_t i=0; i<vector_type::static_size; ++i) {
        for(std::size_t j=0; j<data_t::static_size; ++j) {
            assert(data[j][i] == i);
            data[0][i] *= data[j][i];
        }
    }
}

 



