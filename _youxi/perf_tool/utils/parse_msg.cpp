#include "parse_msg.h"
#include "const.h"

#include <sstream>


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
        if(name.size() > MAX_BODY_LEN) {
            std::cerr << "姓名的长度大于" << MAX_BODY_LEN << "个字节!" <<  std::endl;
            return false;
        }
        
        if(type) {
            *type = MT_BIND_NAME;
        }

        json msg_body;
        msg_body["name"] = name;
        outbuffer = msg_body.dump();
        return true;
        // 聊天消息
    }else if(command == "LaunchTask") {
        std::string task = input.substr(pos+1);
        if(task.size() > MAX_BODY_LEN) {
            std::cerr << "消息的长度大于" << MAX_BODY_LEN << "个字节!" << std::endl;
            return false;
        }

        json msg_body;
        msg_body["information"] = task;
        outbuffer = msg_body.dump();

        if(type) {
            *type = MT_LAUNCH_TASK_MSG;
        }

        return true;
    } else if(command == "SendTaskInfo") {
        std::string task_res = input.substr(pos+1);
        if(task_res.size() > MAX_BODY_LEN) {
            std::cerr << "消息的长度大于" << MAX_BODY_LEN << "个字节!" << std::endl;
            return false;
        }
        
        json msg_body;
        msg_body["information"] = task_res;
        outbuffer = msg_body.dump();

        if(type) {
            *type = MT_SEND_TASK_INFO_MSG;
        }

        return true;
    }
    
    // 不支持的消息类型，返回false
    return false;
}