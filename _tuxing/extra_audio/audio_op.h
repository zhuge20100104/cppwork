#ifndef _AUDIO_OP_H_
#define _AUDIO_OP_H_
#include "common_header.h"

#include <string>

struct AudioOp
{
    AudioOp();
    ~AudioOp();

    void extract_audio(const std::string& src_video, const std::string& dst_audio, 
        AUDIO_OP_ERRORS& err);
    private:
        void adts_header(char* szAdtsHeader, int dataLen);
};
#endif