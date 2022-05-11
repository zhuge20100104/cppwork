#include "locked_device.h"

int main(int argc, char* argv[]) {
    for(unsigned i = 0; i < 10; ++i) {
        boost::optional<locked_device> t = locked_device::try_lock_device();
        if(t) {
            t->use();
            return 0;
        }else {
            std::cout << "...Try again" << std::endl;
        }
    }
    std::cout << "Failure" << std::endl;
    return -1;
}