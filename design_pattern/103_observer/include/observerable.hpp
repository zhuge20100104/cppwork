#ifndef _FREDRIC_OBSERVERABLE_HPP_
#define _FREDRIC_OBSERVERABLE_HPP_

#include <vector>
#include <string>

template <typename T>
struct Observer;

template <typename T>
struct Observerable {
    std::vector<Observer<T>*> observers;

public:
    void notify(T& source, std::string const& field_name) {
        for(auto&& observer: observers) {
            observer->field_changed(source, field_name);
        }
    }

    void subscribe(Observer<T>& observer) {
        observers.push_back(&observer);
    }

    void unsubscribe(Observer<T>& observer) {
        // After std::remove, it will return the last position of the removed container
        // The element between the last position and the container.end will be undefined.
        // So use erase to erase them
        observers.erase(
        std::remove(observers.begin(), observers.end(), &observer)
        , observers.end());
    }
};

#endif