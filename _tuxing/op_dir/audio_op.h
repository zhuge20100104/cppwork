#ifndef _AUDIO_OP_H_
#define _AUDIO_OP_H_
#include "common_header.h"

#include <string>

struct AudioOp
{
    AudioOp();
    ~AudioOp();
    void list_dir(const std::string& dir_name, FILE_OP_ERRORS& err);
    void move_dir(const std::string& src, const std::string& dst,  FILE_OP_ERRORS& err);
    void delete_dir(const std::string& src,  FILE_OP_ERRORS& err);
};
#endif