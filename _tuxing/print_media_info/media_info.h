#ifndef _MEDIA_INFO_H_
#define _MEDIA_INFO_H_
#include "common_header.h"

#include <string>

struct MediaInfo
{
    MediaInfo(const std::string& src_file_name);
    ~MediaInfo();
    void printInfo();

    private:
        std::string filename_;
        AVFormatContext* fmt_ctx {nullptr};
        void init(MediaOpErrors& err);
};
#endif