#include "parse_msg.h"

// 消息解析函数
// input 输入的消息字符串
// type 传出的消息类型指针
// outbuffer 输出的用于发送的消息内容字符串
bool parseMessage(const std::string& input, int* type, std::string& outbuffer) {
    auto pos = input.find_first_of(" ");
    // 消息中没找到空格
    if(pos == std::string::npos) {
        return false;
    }

    if(pos == 0) {
        return false; 
    }

    auto command = input.substr(0, pos);
    // Bind姓名消息
    if(command == "BindName") {
        std::string name = input.substr(pos+1);
        if(name.size()>32) {
            std::cerr << "姓名的长度大于32个字节!" <<  std::endl;
            return false;
        }
        
        if(type) {
            *type = MT_BIND_NAME;
        }
        
        ptree tree;
        tree.put("name", name);
        outbuffer = ptreeToJsonString(tree);
        return true;
        // 聊天消息
    }else if(command == "Chat") {
        std::string chat = input.substr(pos+1);
        if(chat.size() > 256) {
            std::cerr << "消息的长度大于256个字节!" << std::endl;
            return false;
        }
        
        ptree tree;
        tree.put("information", chat);
        outbuffer = ptreeToJsonString(tree);

        if(type) {
            *type = MT_CHAT_INFO;
        }

        return true;
    }   
    
    // 不支持的消息类型，返回false
    return false;
}
