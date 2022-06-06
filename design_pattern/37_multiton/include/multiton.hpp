#ifndef _FREDRIC_MULTITON_HPP_
#define _FREDRIC_MULTITON_HPP_

#include <iostream>
#include <memory>
#include <map>
#include <string>

enum class Importance {
    Primary,
    Secondary,
    Tertiary
};

enum class Size {
    Large,
    Medium,
    Small
};

template <typename T, typename Key = std::string>
class Multiton {
public:
    template<typename ... Args>
    static std::shared_ptr<T> get(Key const& key, Args&& ... args) {
        if(auto const it = instances.find(key); it!=instances.end()) {
            return it->second;
        }

        auto instance = std::make_shared<T>(std::forward<Args>(args)...);
        instances[key] = instance;
        return instance;
    }

private:
    static std::map<Key, std::shared_ptr<T>> instances;

protected:
    Multiton() = default;
    virtual ~Multiton() = default;
};

template <typename T, typename Key>
std::map<Key, std::shared_ptr<T>> Multiton<T, Key>::instances{};

class Printer {
    static int totalInstanceCount;
public:
    Printer() {
        ++ Printer::totalInstanceCount;
        std::cout << "A total of " <<
            Printer::totalInstanceCount <<
            " instances created so far\n";
    }
};

int Printer::totalInstanceCount = 0;


class Circle {
    static int totalInstanceCount;
    float redius {1.0f};
public:
   
    Circle() {
        ++ Circle::totalInstanceCount;
        std::cout << "A total of " <<
            Circle::totalInstanceCount <<
            " circles created so far\n";
    }

    Circle(float redius_): redius {redius_} {
        ++ Circle::totalInstanceCount;
        std::cout << "A total of " <<
            Circle::totalInstanceCount <<
            " circles created so far\n";
    }
};

int Circle::totalInstanceCount = 0;


using MultitonPrinter = Multiton<Printer, Importance>;
using MultitonCircle = Multiton<Circle, Size>;
#endif