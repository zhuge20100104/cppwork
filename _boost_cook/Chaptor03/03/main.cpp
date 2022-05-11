#include <boost/numeric/conversion/cast.hpp>
#include <boost/numeric/conversion/converter.hpp>

#include <iostream>
#include <stdexcept>

void some_function(unsigned short param);
int foo();

void foo1() {
    // 有些编译器可能会警告有数据丢失
    some_function(foo());
}

void foo2() {
    // 编译器不会报警告，看上去像正确的一样
    some_function(
        static_cast<unsigned short>(foo())
    );
}

void correct_implementation() {
    some_function(
        boost::numeric_cast<unsigned short>(foo())
    );
}

void test_function() {
    for(unsigned int i=0; i<100; ++i) {
        try {
            correct_implementation();
        } catch(const boost::numeric::bad_numeric_cast& e) {
            std::cout << '#' << i << ' ' << e.what() << std::endl;
        }
    }
}

void test_function1() {
    for(unsigned int i=0; i<100; ++i) {
        try {
            correct_implementation();
        } catch(const boost::numeric::positive_overflow& e) {
            std::cout << "Positive overflow in: " << i << ' ' << e.what() << std::endl;
        } catch(const boost::numeric::negative_overflow& e) {
            std::cout << "Negative overflow in: " << i << ' ' << e.what() << std::endl;
        }
    }
}

template <class SourceT, class TargetT>
struct my_throw_overflow_handler {
    void operator() (boost::numeric::range_check_result r) {
        if(r != boost::numeric::cInRange) {
            throw std::logic_error("Not in range!");
        }
    }
};

template <class TargetT, class SourceT>
TargetT my_numeric_cast(const SourceT& in) {
    using namespace boost;
    using conv_traits = numeric::conversion_traits<TargetT, SourceT>;
    using cast_traits = numeric::numeric_cast_traits<TargetT, SourceT>;
    using converter = boost::numeric::converter<
        TargetT,
        SourceT,
        conv_traits,
        my_throw_overflow_handler<SourceT, TargetT>
    >;
    return converter::convert(in);
}

int main(int argc, char* argv[]) {
    foo1();
    foo2();
    test_function();
    std::cout << "\n\n\n";
    test_function1();
    std::cout << "\n\n\n";

    short val = 0;
    try {
        val = my_numeric_cast<short>(100000);
    } catch(std::logic_error& e) {
        std::cout << "It works! val = " << val
            << "Error Msg: " << e.what() << std::endl;
    }
}

void some_function(unsigned short param) {
    (void) param;
}

bool some_extremely_rare_condition() {
    static int i = 0;
    ++ i;

    if(i == 50 || i == 150) {
        return true;
    } 

    return false;
}

bool another_extremely_rare_condition() {
    static int i = 0;
    ++ i;

    if(i == 60 || i == 160) {
        return true;
    }
    
    return false;
}

int foo() {
    if(some_extremely_rare_condition()) {
        return -1;
    } else if(another_extremely_rare_condition()) {
        return 1000000;
    }
    return 65535;
}


