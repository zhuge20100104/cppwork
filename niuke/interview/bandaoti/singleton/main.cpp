#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <memory>

using namespace std;

class Singleton {
    Singleton() {++count;}
    Singleton(Singleton const&) = default;
    Singleton& operator=(Singleton const&) = default;
public:
   
    static int count;
    static Singleton& get_singleton() {
        // C++11保证原子性
        static Singleton inst;
        return inst;
    }
};

int Singleton::count = 0;

class Singleton1 {
    Singleton1() {++count;}
    Singleton1(Singleton1 const&) = default;
    Singleton1& operator=(Singleton1 const&) = default;
public:
    static int count;
    static Singleton1* get_singleton() {
        // std::shared_ptr 内部std::atomic保证其原子性
        static shared_ptr<Singleton1> inst(new Singleton1());
        return inst.get();
    }
};

int Singleton1::count = 0;

int main(int argc, char* argv[]) {
    auto count = Singleton::get_singleton().count;
    auto count1 = Singleton::get_singleton().count;
    cout << "Singleton count: " << count << endl;
    cout << "Singleton count: " << count1 << endl;

    auto count11 = Singleton1::get_singleton()->count;
    auto count12 = Singleton1::get_singleton()->count;
    cout << "Singleton1 count: " << count11 << endl;
    cout << "Singleton1 count: " << count12 << endl;

    return EXIT_SUCCESS;
}