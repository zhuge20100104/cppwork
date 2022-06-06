#include "ioc.hpp"

#include <iostream>

struct Base {
    virtual void Func() {}
    virtual ~Base() {}
};

struct DerivedB: public Base {
    public:
        DerivedB(int a, double b): m_a(a), m_b(b) {}
        
        void Func() override {
            std::cout << m_a + m_b << std::endl;
        }

    private:
        int m_a;
        double m_b;
};

struct DerivedC: public Base {
    
};

struct A{
    public:
        A(Base* ptr): m_ptr(ptr) {}
        void Func() {
            m_ptr->Func();
        }

        ~A() {
            if(m_ptr != nullptr) {
                delete m_ptr;
                m_ptr = nullptr;
            }
        }

    private:
        Base* m_ptr;
};

struct Bus {

    Bus(std::string busNo): m_busNo(busNo) {}

    virtual void outputInfo(std::string station) {
        std::cout << "Bus: [" << m_busNo << "] " << "arrived at: " << station << std::endl;
    }
    
    virtual ~Bus(){}
    private:
        std::string m_busNo;
};

struct BigBus: public Bus {
    BigBus(std::string bigNo):Bus(bigNo), m_bigNo(bigNo) {
        std::cout << "This is a big bus [" << m_bigNo  << "]" << std::endl;
    }

    void outputInfo(std::string No) override {
        std::cout << "BigBus can take: [" << No << "] " << "people" << std::endl;
    }

    private:
        std::string m_bigNo;
};



int main() {
    // 这个IOC不算特别好用，必须要写清楚构造函数依赖的参数才行 
    IocContainer ioc;
    // A依赖 DerivedC, DerivedC不带参数
    ioc.RegisterType<A, DerivedC>("C");
    auto c = ioc.ResolveShared<A>("C");

    // A依赖 DerivedB, DerivedB带一个int 和double参数
    ioc.RegisterType<A, DerivedB, int, double>("B");
    auto b = ioc.ResolveShared<A>("B", 1, 2.0);
    b->Func();
    // 多次调用ResolveShared获取多个实例
    auto d = ioc.ResolveShared<A>("B", 3, 2.0);
    d->Func();

    // 注册简单对象, 带一个std::string参数
    ioc.RegisterSimple<Bus, std::string>("Bus");
    auto bus = ioc.ResolveShared<Bus>("Bus", std::string("11"));
    bus->outputInfo("知春路");

    // 注册父子对象，带一个std::string参数
    ioc.RegisterType<Bus, BigBus, std::string>("BB");
    auto bb = ioc.ResolveShared<Bus>("BB", std::string("B12"));
    bb->outputInfo("100");
}
