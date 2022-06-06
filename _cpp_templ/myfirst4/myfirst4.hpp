#ifndef _FREDRIC_MY_FIRST4_HPP_
#define _FREDRIC_MY_FIRST4_HPP_

#include "glog/logging.h"
#include <boost/type_index.hpp>

#if defined(USE_EXPORT)
#define EXPORT export
#else
#define EXPORT
#endif

EXPORT 
template <typename T>
void print_typeof(T const&);

#ifndef USE_EXPORT
template <typename T>
void print_typeof(T const& x) {
    LOG(INFO) << boost::typeindex::type_id_runtime(x);
}
#endif
#endif