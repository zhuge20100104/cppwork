#include "func.h"

#include <ctype.h>

std::string ToUpper(const std::string& str) {
    std::string res;
    for (auto& ch : str) {
        res += toupper(ch);
    }
    return std::move(res);
}

std::vector<int> findAll(const std::string& target,
                         const std::string& search_string,
                         std::size_t offset
    ) {
    std::vector<int> res;
    std::size_t cur_pos = offset;
    while (true) {
        std::size_t find_pos = target.find(search_string, cur_pos);
        if (find_pos == std::string::npos) {
            break;
        } else {
            res.emplace_back(find_pos);
        }
        cur_pos = find_pos + search_string.size();
    }
    return std::move(res);
}

std::vector<int> FindAll(const std::string& target,
                         const std::string& search_string, 
                         Case searchCase,
                         std::size_t offset) {
    
    // 区分大小写比较
    if (searchCase == Case::SENSITIVE) {
        return std::move(findAll(target, search_string, offset));
    }
    // 不区分大小写比较
    std::string src {std::move(ToUpper(target))};
    std::string dst {std::move(ToUpper(search_string))};
    return std::move(findAll(src, dst, offset));
}
