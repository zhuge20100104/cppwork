#include <iostream>
#include <memory>
using std::cout;
using std::endl;
#include "lazy.hpp"
#include <cstdlib>

// 用于测试延时加载的大对象
struct BigObject {
    BigObject() {
        cout << "Lazy load big object..." << endl;
    }
};

struct MyStruct {
    MyStruct() {
        m_obj = lazy([]{return std::make_shared<BigObject>();});
    }

    // 调用.Value函数真正调用lambda函数，加载大对象
    void Load() {
        m_obj.Value();
    }

    private:
        Lazy<std::shared_ptr<BigObject> > m_obj;
};

int Foo(int x) {
    return 2 * x;
}

void testLazy() {
    // 普通函数延时加载
    int y = 4;
    auto lazyer1 = lazy(Foo, y);
    cout << lazyer1.Value() << endl;

    // 不带参数的lambda
    auto lazyer2 = lazy([] {return 12;});
    cout << lazyer2.Value() << endl;

    // 带参数的std::function调用
    std::function<int(int)> f = [](int x) {return x+3; };
    auto lazyer3 = lazy(f, 3);
    cout << lazyer3.Value() << endl;

    // 大对象延时加载
    MyStruct t;
    t.Load();
}

int main(void) {
    testLazy();
    
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
