#ifndef _FREDRIC_OBSERVERABLE_HPP_
#define _FREDRIC_OBSERVERABLE_HPP_

#include <vector>
#include <string>
#include <mutex>
#include <algorithm>

template <typename T>
struct Observer;

template <typename T>
struct Observerable {
    std::vector<Observer<T>*> observers;

    std::mutex mtx;


public:
    void notify(T& source, std::string const& field_name) {
        std::scoped_lock<std::mutex> lock{mtx};
        for(auto&& observer: observers) {
            if(observer){ // 这里要判空
                observer->field_changed(source, field_name);
            }
        }
    }

    void subscribe(Observer<T>& observer) {
        std::scoped_lock<std::mutex> lock{mtx};
        observers.push_back(&observer);
    }

    void unsubscribe(Observer<T>& observer) {
        // 有可能unsubscribe的时候，正在notify，
        // 这个时候如果这里加锁，会产生死锁，同时对一个互斥元加锁两次
        auto it = std::find(observers.begin(), observers.end(), &observer);
        if(it != observers.end()) {
            *it = nullptr;
        }
    }
};

#endif