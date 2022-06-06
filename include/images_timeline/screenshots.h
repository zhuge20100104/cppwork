#ifndef _FREDRIC_SCREENSHOTS_H_
#define _FREDRIC_SCREENSHOTS_H_

#include <iostream>
#include <map>
#include <string>
#include <vector>

using screenshots_value_type = std::map<std::string, std::vector<std::string>>;
using meta_type = std::map<std::string, std::string>;

struct screenshots {
    std::string product_key;
    screenshots_value_type old_value;
    screenshots_value_type new_value;
    meta_type meta;
    std::string change_time;
    friend std::ostream& operator<<(std::ostream& os,
                                    const screenshots& screenshots_);
};

struct icon_url {
    std::string product_key;
    std::string old_url;
    std::string new_url;
    std::string change_time;

    friend std::ostream& operator<<(std::ostream& os,
        const icon_url& icon_url_);
};

#endif