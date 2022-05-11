#include "csm2.hpp"

#include "csmtraits.hpp"

#include <iostream>
#include <cstdlib>
#include <string>
#include <memory>

struct MyClass {
    std::string name;
    MyClass(std::string const& name_): name{name_} {
    }
};

int main(int argc, char* argv[]) {
    
    CSMTraits<MyClass> clsTraits;
    MyClass src{"张三"};
    MyClass dst{"李四"};

    clsTraits.move(&src, &dst);
    std::cout << "After move: " << dst.name << std::endl;


    std::cout << "After move..." << std::endl;

    MyClass sources[] = {
        {"张三"}, {"李四"}, {"王五"}
    };

    void* dstes = malloc(3 * sizeof(MyClass));
    clsTraits.move_init_n(sources, dstes, 3);
    
    
    MyClass* dst_myclass = (MyClass*)dstes;
    std::cout << "After move init n..." << std::endl;

    for(int i=0; i<3; ++i) {
        std::cout << dst_myclass[i].name << std::endl;
    }
    
    free(dstes);

    return EXIT_SUCCESS;
}