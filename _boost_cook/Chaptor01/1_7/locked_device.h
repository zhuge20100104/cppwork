#ifndef _LOCK_DEVICE_H_
#define _LOCK_DEVICE_H_
#include <iostream>
#include <boost/optional.hpp>

class locked_device {
    explicit locked_device(const char* /*param*/) {
        std::cout << "Device is locked" << std::endl;
    }

    static bool try_lock_device_impl();

    public:
        void use() {
            std::cout << "Success!\n";
        }   

        static boost::optional<locked_device> try_lock_device() {
            if(!try_lock_device_impl()) {
                return boost::none;
            }
            // Lock成功
            return locked_device("device1");
        }

        ~locked_device();
};
#endif
