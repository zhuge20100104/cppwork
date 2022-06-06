#include "locked_device.h"

locked_device::~locked_device() {}

bool locked_device::try_lock_device_impl() {
    static int i = 0;
    ++i;
    return i == 3;
}
