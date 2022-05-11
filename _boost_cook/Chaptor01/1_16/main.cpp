#include <iostream>

class descriptor_owner {
    char* descriptor_;

public:
    explicit descriptor_owner(const char* params);
    
    ~descriptor_owner() {
        if(descriptor_) {
            delete [] descriptor_;
            descriptor_ = nullptr;
        }
    }
};


descriptor_owner::descriptor_owner(const char*) {
    descriptor_ = new char[10];
}

void i_am_bad() {
    descriptor_owner d1("O-o");
    descriptor_owner d2("^_^");

    d2 = d1;
    // destructor of d2 will free the descriptor
    // destructor of d1 will try to free already freed descriptor
}

int main(int argc, char* argv[]) {
    i_am_bad();
} 
