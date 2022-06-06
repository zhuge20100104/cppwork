#ifndef _FREDRIC_JOURNAL_H_
#define _FREDRIC_JOURNAL_H_

#include <string>
#include <vector>
#include <iostream>

struct Journal {
    std::string title;
    std::vector<std::string> entries;
    Journal(std::string const& title);
    void add_entry(std::string const& entry);
};
#endif