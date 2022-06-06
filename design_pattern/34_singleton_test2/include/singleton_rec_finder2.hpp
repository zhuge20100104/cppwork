#ifndef _FREDRIC_SINGLETON_DB_HPP_
#define _FREDRIC_SINGLETON_DB_HPP_
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <concepts>
#include <map>
#include <utility>

template <typename T>
concept DBType = requires (T value) {
    {value.get_population(std::declval<std::string const&>())} -> std::convertible_to<int>;
};

class SingletonDatabase {
    // 私有构造函数，不可外部构造
    SingletonDatabase() {
        std::cout << "Initializing database\n";
        std::ifstream ifs{"../data/capitals.txt"};
        std::string s, s2;
        while(std::getline(ifs, s)) {
            std::getline(ifs, s2);
            int pop = std::atoi(s2.c_str());
            capitals[s] = pop;
        }
    }
    std::map<std::string, int> capitals;

public:
    // 不允许拷贝和赋值
    SingletonDatabase(SingletonDatabase const&) = delete;
    SingletonDatabase& operator=(SingletonDatabase const&) = delete;

    static SingletonDatabase& get() {
        // C++ 11保证此处线程安全
        static SingletonDatabase db;
        return db;
    }

    int get_population(std::string const& name) {
        return capitals[name];
    }
};

class DummyDatabase {
    std::map<std::string, int> capitals {};
public:
    DummyDatabase() {
        capitals["alpha"] = 1;
        capitals["beta"] = 2;
        capitals["gamma"] = 3;
    }

    int get_population(std::string const& name) {
        return capitals[name];
    }
};

template <DBType DB>
struct ConfigurableRecordFinder {
    DB& db;
    ConfigurableRecordFinder(DB& db_): db(db_) {}

    int total_population(std::vector<std::string> const& names) {
        int result {0};
        for(auto& name: names) {
            result += db.get_population(name);
        }
        return result;
    }
};


#endif