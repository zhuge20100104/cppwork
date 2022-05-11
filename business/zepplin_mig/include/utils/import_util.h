#ifndef _FREDRIC_ZEPPLIN_MIG_IMPORT_UTIL_H_
#define _FREDRIC_ZEPPLIN_MIG_IMPORT_UTIL_H_

#include <string>

struct DbsPath {
    std::string path;
    std::string dir;
    bool is_valid;
};

struct ImportUtil {
    static bool import_note_books(std::string const& note_path);
};

#endif