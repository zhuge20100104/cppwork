#ifndef _PARSE_MSG_H_
#define _PARSE_MSG_H_
#include "json_object.h"

#include <sstream>
#include <cstdlib>
#include <string>
#include <iostream>
#include <cstring>


struct Header {
    int bodySize; // 包体大小 
    int type; // 消息类型
};

enum MessageType {
    MT_BIND_NAME = 1,
    MT_CHAT_INFO = 2,
    MT_ROOM_INFO = 3,
};

bool parseMessage(const std::string& input, int* type, std::string& outbuffer);
#endif
