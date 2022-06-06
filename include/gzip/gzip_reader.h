#ifndef _FREDRIC_GZIP_READER_H_
#define _FREDRIC_GZIP_READER_H_

#include <string>

struct gzip_reader {
  
    static std::string read_file(const std::string& file_name);
};
#endif