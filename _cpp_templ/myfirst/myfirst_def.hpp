#ifndef _FREDRIC_MY_FIRST_DEF_HPP_
#define _FREDRIC_MY_FIRST_DEF_HPP_

#include "glog/logging.h"
#include <boost/type_index.hpp>

template <typename T>
void print_typeof(T const& x) {
    LOG(INFO) << boost::typeindex::type_id_runtime(x).pretty_name(); 
}

#endif