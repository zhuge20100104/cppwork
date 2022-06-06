#ifndef _STRUCT_HEADER_H_
#define _STRUCT_HEADER_H_ 
#include <string>
#include <iostream>
#include <cstring>
// 注意一下消息体的设计，都是以4字节的大小为单位的
// 这是为了字节对齐，
// 而且消息体中的字段类型都是POD类型
// 这些都是有意为之

struct Header {
    int bodySize; // 包体大小 
    int type; // 消息类型
};

enum MessageType {
    MT_BIND_NAME = 1,  // 绑定姓名消息
    MT_CHAT_INFO = 2,  // 聊天信息消息
    MT_ROOM_INFO = 3,  // 聊天室消息
};

// 客户端发送
struct BindName {
    char name[32]; // name字段
    int nameLen; // name的实际长度
};


// 客户端发送
struct ChatInformation {
    char information[256];  // 聊天消息  
    int infoLen;  // 消息长度
};


// 服务端发送
struct RoomInformation {
    BindName name;    // 绑定姓名消息
    ChatInformation chat;   // 聊天信息消息
};

bool parseMessage(const std::string& input, int* type, std::string& outbuffer);
#endif
