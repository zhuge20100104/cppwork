#ifndef _CHAT_MESSAGE_H_
#define _CHAT_MESSAGE_H_

#include "Protocal.pb.h"
#include "parse_msg.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iostream>


class chat_message {
    public:
        // Header的大小变为8个字节
        enum { header_length = 8 };
        enum { max_body_length = 512 };

        chat_message() {}
        
        // 这里返回的data不可以修改
        const char* data() const { return data_; }
        char* data() { return data_; }
        
        // 计算总长度时，需要通过m_header获取到bodySize
        std::size_t length() const { return header_length + m_header.bodysize(); }
        
        // body为 data_往后面移动 head_length个字节
        const char* body() const { return data_ + header_length; }
        char* body() { return  data_ + header_length; }
        
        int type() const { return m_header.type(); }


        std::size_t body_length() const { return m_header.bodysize(); }

        void setMessage(int messageType, const void* buffer, size_t bufferSize) {
            // 确认body大小未超过限制
            assert(bufferSize < max_body_length);

            m_header.set_bodysize(bufferSize);
            m_header.set_type(messageType);

            std::memcpy(body(), buffer, bufferSize);
            std::string headerBuf;
            m_header.SerializeToString(&headerBuf);
            std::memcpy(data(), headerBuf.data(), sizeof(headerBuf));
        }

        void setMessage(int messageType, const std::string& buffer) {
            setMessage(messageType, buffer.data(), buffer.size());
        }

        bool decode_header() {
            std::string headerBuf(data(), data()+header_length);
            m_header.ParseFromString(headerBuf);

            if(m_header.bodysize()> max_body_length) {
                std::cout <<"body size: " << m_header.bodysize() << " header type:" << m_header.type()  << std::endl;
                return false;
            }

            return true;
        }
        
    private:
        char data_[header_length+max_body_length];
        PHeader m_header;
};
#endif
