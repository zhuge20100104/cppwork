#ifndef _FREDIRC_LINK_ITEM_H_
#define _FREDIRC_LINK_ITEM_H_
#include <string>

struct LinkItem {
    std::string name;
    std::string url;
};

template <typename T>
struct Result {
    bool res;
    T obj;
};
#endif