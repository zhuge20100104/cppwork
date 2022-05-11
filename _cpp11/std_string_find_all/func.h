#ifndef _FREDRIC_FUNC_H_
#define _FREDRIC_FUNC_H_
#include <vector>
#include <string>
#include <iostream>

enum class Case {SENSITIVE, INSENSITIVE};

std::string ToUpper(const std::string& str);

std::vector<int> FindAll(
    const std::string& target,
    const std::string& search_string,
    Case searchCase = Case::INSENSITIVE,
    std::size_t offset = 0
);
#endif