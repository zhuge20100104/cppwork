#include <iostream>
#include <string>
#include <typeinfo>
#include <memory>
#include <cstdlib>

#ifndef _MSC_VER
#include <cxxabi.h>
#endif

using std::string;
using std::cout;
using std::endl;
using std::unique_ptr;
using std::remove_reference;

template <class T>
string type_name() {
    using TR = typename remove_reference<T>::type;
    unique_ptr<char, void(*)(void*)>  own(
#ifndef __GNUC__
            nullptr,
#else
            abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr),
#endif 
            std::free);

    string r = own!=nullptr ? own.get(): typeid(TR).name();

    if(std::is_const<TR>::value) {
        r += "const";
    }else if(std::is_volatile<TR>::value) {
        r += "volatile";
    }else if(std::is_lvalue_reference<T>::value) {
        r += "&";
    }else if(std::is_rvalue_reference<T>::value) {
        r += "&&";
    }

    return r;
}

template <typename T>
void Func(T && t) {
    cout << type_name<T>() << endl;
}


int main(void) {
    string str = "Test";
    Func(str);
    Func(std::move(str));
    
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
