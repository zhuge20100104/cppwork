#include "string_conv.h"
#include <ctype.h>

std::string ToUpper(const std::string& str) {
    std::string res;
    for(auto& ch: str) {
        res += toupper(ch);
    }
    return std::move(res);
}

std::string ToLower(const std::string& str) {
    std::string res;
    for(auto& ch: str) {
        res += tolower(ch);
    }
    return std::move(res);
}