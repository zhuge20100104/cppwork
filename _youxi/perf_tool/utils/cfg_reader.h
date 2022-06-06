#ifndef _FREDRIC_CFG_READER_H_
#define _FREDRIC_CFG_READER_H_

#include <map>
#include <string>

struct cfg_reader {
    static bool read_file(const std::string& file_name_, std::map<std::string, std::string>& cfg_);
};

#endif