#include <boost/noncopyable.hpp>

#include <iostream>

class descriptor_owner_fixed: private boost::noncopyable {
    char* descriptor_;

public:
    explicit descriptor_owner_fixed(const char* params);
    
    ~descriptor_owner_fixed() {
        if(descriptor_) {
            delete [] descriptor_;
            descriptor_ = nullptr;
        }
    }
};


descriptor_owner_fixed::descriptor_owner_fixed(const char*) {
    descriptor_ = new char[10];
}

void i_am_good() {
    descriptor_owner_fixed d1("O-o");
    descriptor_owner_fixed d2("^_^");

    d2 = d1;
}

int main(int argc, char* argv[]) {
    i_am_good();
} 
