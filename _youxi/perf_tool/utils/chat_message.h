#ifndef _CHAT_MESSAGE_H_
#define _CHAT_MESSAGE_H_

#include "parse_msg.h"
#include "const.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iostream>
#include <memory>

class chat_message {
    public:
        // Header的大小变为8个字节，使用sizeof关键字进行计算
        enum { header_length = sizeof(Header) };
        enum { max_body_length = MAX_BODY_LEN};

        chat_message() {
            data_ = std::shared_ptr<char>(new char[header_length+max_body_length], std::default_delete<char[]>());
        }
        
        // 这里返回的data不可以修改
        const char* data() const { return data_.get(); }
        char* data() { return data_.get(); }
        
        // 计算总长度时，需要通过m_header获取到bodySize
        std::size_t length() const { return header_length + m_header.bodySize; }
        
        // body为 data_往后面移动 head_length个字节
        const char* body() const { return data_.get() + header_length; }
        char* body() { return  data_.get() + header_length; }
        
        int type() const { return m_header.type; }


        std::size_t body_length() const { return m_header.bodySize; }

        void setMessage(int messageType, const void* buffer, size_t bufferSize) {
            // 确认body大小未超过限制
            assert(bufferSize < max_body_length);
            m_header.bodySize = bufferSize;
            m_header.type = messageType;
            std::memcpy(body(), buffer, bufferSize);
            std::memcpy(data(), &m_header, sizeof(m_header));
            char* body_ = body();
            std::cerr << "set message body=" << body_ << std::endl;
        }

        void setMessage(int messageType, const std::string& buffer) {
            setMessage(messageType, buffer.data(), buffer.size());
        }

        bool decode_header() {
            std::memcpy(&m_header, data(), header_length);
            if(m_header.bodySize > max_body_length) {
                std::cout <<"body size: " << m_header.bodySize << " header type:" << m_header.type  << std::endl;
                return false;
            }

            return true;
        }
        
    private:
        std::shared_ptr<char> data_;
        Header m_header;
};

#endif
