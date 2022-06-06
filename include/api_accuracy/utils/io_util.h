#ifndef _FREDRIC_IO_UTIL_H_
#define _FREDRIC_IO_UTIL_H_

#include <string>

struct IOUtil {
    static std::string read_file(const std::string& file_name);
    static bool write_file(const std::string& file_name, const std::string& content);
};

#endif