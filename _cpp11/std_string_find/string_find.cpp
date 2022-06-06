#include "string_find.h"

#include <ctype.h>

std::string ToUpper(const std::string& str) {
    std::string res;
    for(auto& ch: str) {
        res += toupper(ch);
    }
    return std::move(res);
}

std::size_t Find(
    const std::string& source,
    const std::string& search_string,
    Case searchCase,
    std::size_t offset
) {
    // 区分大小写比较
    if(searchCase == Case::SENSITIVE) {
        return source.find(search_string, offset);
    }
    // 不区分大小写比较
    std::string in_source {ToUpper(source)};
    std::string in_search {ToUpper(search_string)};
    return in_source.find(in_search, offset);
}