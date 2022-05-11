#include <boost/cast.hpp>

#include <iostream>

struct object {
    virtual ~object() {}
};

struct banana: public object
{
    void eat() const {}
    virtual ~banana() {}
};

struct pidgin: public object {
    void fly() const {}
    virtual ~pidgin() {}
};

object* try_product_banana();

void try_eat_banana_impl1() {
    const object* obj = try_product_banana();
    if(!obj) {
        throw std::bad_cast();
    }

    dynamic_cast<const banana&>(*obj).eat();
}

void try_eat_banana_impl2() {
    const object* obj = try_product_banana();
    boost::polymorphic_cast<const banana*>(obj)->eat();
}

object* try_product_banana() {
    static pidgin pidg;
    static banana bana;
    
    static int i = 0;
    ++ i;
    
    if(i==3 || i==6) {
        std::cout << "i=" << " " << i << " null banana" << std::endl;;
        return nullptr;
    }else if(i==2 || i==5) {
        std::cout << "i=" << " " << i << " pidgin" << std::endl;
        return &pidg;
    }
    std::cout << "i=" << i << " banana" << std::endl;
    return &bana;
}

int main(int argc, char* argv[]) {
    try_eat_banana_impl1();
    try {
        try_eat_banana_impl1();
        assert(false);
    }catch(...) {}   

    try_eat_banana_impl2();
    try{
        try_eat_banana_impl2();
        assert(false);
    } catch(...) {}

    try_eat_banana_impl2();
    try{
        try_eat_banana_impl2();
        assert(false);
    } catch(...) {}

    return 0;
}
