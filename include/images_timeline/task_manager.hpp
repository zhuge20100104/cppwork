#ifndef _FREDRIC_TASK_MANAGER_HPP_
#define _FREDRIC_TASK_MANAGER_HPP_

#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>

#include <vector>

template <typename T>
using task_function_type = std::function<void(const std::vector<T>&, int&)>;

template <typename T>
struct task_manager {
    task_manager(const std::vector<T>& all_eles, const int batch_size)
        : all_eles_{all_eles}, batch_size_{batch_size} {
        batches_ = all_eles_.size() / batch_size_ + 1;

        for (int i = 0; i < batches_; ++i) {
            compared_failed_nums.push_back(0);
        }
    }

    void divide_elements_to_batches() {
        sub_eles_.clear();
        for (int i = 0; i < batches_; ++i) {
            std::vector<T> sub_ele{};
            if (i + 1 < batches_) {
                for (int j = 0; j < batch_size_; ++j) {
                    sub_ele.emplace_back(
                        std::move(all_eles_[i * batch_size_ + j]));
                }
            } else {
                for (int j = 0; j < all_eles_.size() % batch_size_; ++j) {
                    sub_ele.emplace_back(
                        std::move(all_eles_[i * batch_size_ + j]));
                }
            }
            sub_eles_.emplace_back(std::move(sub_ele));
        }
    }

    void start_thread_pool_and_run_tasks(const task_function_type<T>& func) {
        // 使用asio thread_pool启动线程池，运行子任务
        boost::asio::thread_pool pool{batches_};
        for (int i = 0; i < sub_eles_.size(); ++i) {
            boost::asio::post(pool,
                              std::bind(func, std::ref(sub_eles_[i]),
                                        std::ref(compared_failed_nums[i])));
        }
        pool.join();
    }

    int collect_failed_count() {
        int total_failed_num{0};
        for (auto failed_num : compared_failed_nums) {
            total_failed_num += failed_num;
        }
        return total_failed_num;
    }

   private:
    std::vector<T> all_eles_{};
    int batch_size_{};
    std::size_t batches_{};
    std::vector<std::vector<T>> sub_eles_{};
    std::vector<int> compared_failed_nums{};
};
#endif