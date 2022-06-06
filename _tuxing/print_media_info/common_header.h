#ifndef _COMMON_HEADER_H_
#define _COMMON_HEADER_H_
#define __STDC_CONSTANT_MACROS

#pragma warning(disable:4996)
#include <stdio.h>
#include <type_traits>
#include <iostream>
#include <exception>
#include <string>

extern "C" {
	#include <libavutil/log.h>
	#include <libavformat/avformat.h>
	#include <libavformat/avio.h>
}


// MediaOpenExcept 打开媒体文件异常
class MediaOpenExcept: public std::exception {
	public:
		MediaOpenExcept(): message_{"打开媒体文件错误"} {}
		const char* what() const noexcept(true) {
			return message_.c_str();
		}

	private:
		std::string message_;
};

enum class MediaOpErrors {
  	NO_ERROR,   // 0， 无错误 
	OPEN_MEDIA_ERROR, // 1, 打开媒体文件错误
	FIND_STREAM_ERROR, // 2, 查找流信息错误
};

template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}
#endif
