#include <boost/scoped_array.hpp>

#include <stdexcept>
#include <cassert>

void may_throw1(const char* buffer);
void may_throw2(const char* buffer);

void foo() {
    // 不能在栈上分配10MB内存，所以
    // 我们在堆上分配10MB
    const char* buffer = new char[1024 * 1024 * 10];

    // 这里有几段可能会throw的代码
    may_throw1(buffer);
    may_throw2(buffer);

    delete [] buffer;
}

void foo_fixed() {
    // 我们接着在堆上分配这段内存，但是
    // 我们使用boost::scoped_array来管理堆内存的生命周期
    boost::scoped_array<char> buffer(new char[1024 * 1024 * 10]);
    // 这里的两段代码可能会throw Exception，
    // 但是现在exception 抛出不会再导致内存泄漏
    may_throw1(buffer.get());
    may_throw2(buffer.get());
    // buffer的析构函数将会调用delete []
}

void may_throw1(const char* /*buffer*/ ) {
    // 啥也不做
}

void may_throw2(const char* buffer) {
    throw std::exception();
}

int main(int argc, char* argv[]) {
    try {
        foo_fixed();
    } catch(...) {

    }
    return 0;
}





