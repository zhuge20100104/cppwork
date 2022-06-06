#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/lexical_cast.hpp>

#include <map>
#include <string>
#include <chrono>
#include <iostream>

struct user_info {
    std::string address;
    unsigned short age;
};

// 使用传统锁和互斥体，不能同时读或者写
// 三种情况 读-读不行， 写-写不行， 读-写不行
namespace first_example {
    class users_online {
        using mutex_t = boost::mutex;
        mutable mutex_t users_mutex_;
        std::map<std::string, user_info> users_;

    public:
        bool is_online(const std::string& username) const {
            boost::lock_guard<mutex_t> lock(users_mutex_);
            return users_.find(username) != users_.end();
        }

        unsigned short get_age(const std::string& username) const  {
            boost::lock_guard<mutex_t> lock(users_mutex_);
            return users_.at(username).age;
        }

        void set_online(const std::string& username, const user_info& data) {
            boost::lock_guard<mutex_t> lock(users_mutex_);
            users_.insert(std::make_pair(username, data));
        }
    };
};

// 使用共享锁和共享互斥体，能同时读，不能同时写
// 三种情况，读-读可以，写-写不行，读-写不行
namespace shared_lock_example {
    class users_online {
        using mutex_t = boost::shared_mutex;
        mutable mutex_t users_mutex_;
        std::map<std::string, user_info> users_;

    public:
        bool is_online(const std::string& username) const {
            boost::shared_lock<mutex_t> lock(users_mutex_);
            return users_.find(username) != users_.end();
        }

        unsigned short get_age(const std::string& username) const  {
            boost::shared_lock<mutex_t> lock(users_mutex_);
            return users_.at(username).age;
        }

        void set_online(const std::string& username, const user_info& data) {
            boost::lock_guard<mutex_t> lock(users_mutex_);
            users_.insert(std::make_pair(username, data));
        }
    };
};

const std::size_t users_count = 1000000;

template <class T>
void log_in(T& u, std::size_t count) {
    for(std::size_t i=0; i<count; ++i) {
        u.set_online(boost::lexical_cast<std::string>(i), user_info());
    }
}

template <class T>
void thread_get_age(const T& u) {
    for(std::size_t i=0; i<users_count; ++i) {
        u.get_age(boost::lexical_cast<std::string>(i));
    }
}

template <class T>
void thread_is_online(const T& u) {
    for(std::size_t i=0; i<users_count; ++i) {
        assert(u.is_online(boost::lexical_cast<std::string>(i)));
    }
}

using locked_users_online = first_example::users_online;
using shared_users_online = shared_lock_example::users_online;

template <class T>
void test_lock_time(const T& users, const std::string& lock_type) {

    auto before_time = std::chrono::steady_clock::now();

    boost::thread t1([&users](){
        thread_get_age<T>(users);
    });
    boost::thread t2([&users](){
        thread_get_age<T>(users);
    });
    boost::thread t3([&users](){
        thread_is_online<T>(users);
    });
    boost::thread t4([&users](){
        thread_is_online<T>(users);
    });

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    auto after_time = std::chrono::steady_clock::now();
    double duration_mills = std::chrono::duration<double, std::milli>(after_time - before_time).count();
    std::cout << "使用" << lock_type << "， 花费毫秒数: " << duration_mills << std::endl;
}

int main(int argc, char* argv[]) {
    locked_users_online locked_users;
    shared_users_online shared_users;
    log_in(locked_users, users_count);
    log_in(shared_users, users_count);
    
    test_lock_time<locked_users_online>(locked_users, "传统锁");
    test_lock_time<shared_users_online>(shared_users, "共享锁");
    return 0;
}