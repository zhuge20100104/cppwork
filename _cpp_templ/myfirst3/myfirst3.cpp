#include "myfirst3.hpp"

#include "glog/logging.h"

#include <boost/type_index.hpp>

template <typename T>
void print_typeof(T const& x) {
    LOG(INFO) << boost::typeindex::type_id_runtime(x).pretty_name();
}
