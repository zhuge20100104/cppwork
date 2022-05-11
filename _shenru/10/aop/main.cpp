#include "timer.hpp"
#include "aspect.hpp"

#include <iostream>

using namespace _time;


struct TimeElapsedAspect {

    void Before(int i) {
        m_lastTime = m_t.elapsed();
    }

    void After(int i) {
        std::cout << "Time elapsed: " << m_t.elapsed() - m_lastTime << std::endl;
    }

    private:
        double m_lastTime;
        Timer m_t;
};

struct LoggingAspect {

    void Before(int i) {
        std::cout << "Entering..." << std::endl;
    } 

    void After(int i) {
        std::cout << "Leaving..." << std::endl;
    }
};

void foo(int a) {
    std::cout << "Real HT function..." << a << std::endl;
}

int main() {
    // Aspect的调用是一个调用栈，满足先进后出的原则
    Invoke<LoggingAspect, TimeElapsedAspect>(&foo, 1);
    std::cout << "-----------------------------------------" << std::endl;
    Invoke<TimeElapsedAspect, LoggingAspect>(&foo, 1);
}
