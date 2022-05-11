#include "journal.h"


Journal::Journal(std::string const& title_): title(title_) {
}

void Journal::add_entry(std::string const& entry) {
    int static count = 1;
    entries.push_back(std::to_string(count++) + ":" + entry);
}