#ifndef _FREDRIC_PERSIS_MANAGER_H_
#define _FREDRIC_PERSIS_MANAGER_H_

#include "journal.h"

struct PersisManager {
    static void save(Journal const& j, std::string const& file_name);
};

#endif