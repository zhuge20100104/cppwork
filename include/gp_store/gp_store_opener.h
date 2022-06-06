#ifndef _FREDRIC_GP_STORE_OPENER_H_
#define _FREDRIC_GP_STORE_OPENER_H_

#include <vector>
#include <string>

struct gp_store_opener
{
    bool get_a_country(const std::string& country_code);
    std::vector<std::string> read_all_language_code();        
};

#endif