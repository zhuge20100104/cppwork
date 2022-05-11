#ifndef _FREDRIC_ENTITY_H_
#define _FREDRIC_ENTITY_H_
#include <stddef.h>
#include <string>

struct Entity {
    int64_t product_id;
    std::string old_url;
    std::string new_url;
    std::string date;
};
#endif