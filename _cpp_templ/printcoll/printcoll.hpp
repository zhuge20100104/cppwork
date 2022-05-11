#ifndef _FREDRIC_PRINT_COLL_HPP_
#define _FREDRIC_PRINT_COLL_HPP_

#include "glog/logging.h"

#include <sstream>

template <typename CONT>
void printcoll(CONT const& coll) {
    std::stringstream ss;
    typename CONT::const_iterator pos; //迭代器当前位置
    typename CONT::const_iterator end(coll.end()); //结束位置

    for(pos=coll.begin(); pos!=end; ++pos) {
        ss << *pos << " ";
    }
    ss << "\n";
    LOG(INFO) << ss.str();
}
#endif