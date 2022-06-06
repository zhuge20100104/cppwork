#ifndef _FREDRIC_STRING_FIND_H_
#define _FREDRIC_STRING_FIND_H_

#include <string>

enum class Case {SENSITIVE, INSENSITIVE};

std::string ToUpper(const std::string& str);

std::size_t Find(
    const std::string& source,
    const std::string& search_string,
    Case searchCase = Case::INSENSITIVE,
    std::size_t offset = 0
);

#endif