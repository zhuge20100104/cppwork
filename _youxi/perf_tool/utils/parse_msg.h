#ifndef _FREDRIC_PARSE_MSG_H_
#define _FREDRIC_PARSE_MSG_H_

#include "json/json.hpp"

#include <sstream>
#include <cstdlib>
#include <string>
#include <iostream>
#include <cstring>

using json = nlohmann::json;


struct Header {
    int bodySize; // 包体大小 
    int type; // 消息类型
};

enum MessageType {
    MT_BIND_NAME = 1,
    MT_LAUNCH_TASK_MSG = 2,
    MT_SEND_TASK_INFO_MSG = 3, 
};

bool parseMessage(const std::string& input, int* type, std::string& outbuffer);
#endif
