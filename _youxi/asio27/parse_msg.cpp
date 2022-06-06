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
        
        PBindName bindName;
        bindName.set_name(name);
        auto ok = bindName.SerializeToString(&outbuffer);
        return ok;
        // 聊天消息
    }else if(command == "Chat") {
        std::string chat = input.substr(pos+1);
        if(chat.size() > 256) {
            std::cerr << "消息的长度大于256个字节!" << std::endl;
            return false;
        }
        
        
        PChat pchat;
        pchat.set_information(chat);
        auto ok = pchat.SerializeToString(&outbuffer);

        if(type) {
            *type = MT_CHAT_INFO;
        }

        return ok;
    }   
    
    // 不支持的消息类型，返回false
    return false;
}
