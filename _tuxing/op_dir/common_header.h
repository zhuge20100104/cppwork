#ifndef _COMMON_HEADER_H_
#define _COMMON_HEADER_H_
#define __STDC_CONSTANT_MACROS

#pragma warning(disable:4996)
#include <stdio.h>
#include <type_traits>
#include <iostream>

extern "C" {
	#include <libavutil/log.h>
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
	#include <libavformat/avio.h>
}


enum class FILE_OP_ERRORS {
  	NO_ERROR,   // 0， 无错误 
	OPEN_DIR_ERROR, // 1, 打开目录错误
	READ_DIR_ERROR, // 2, 读取目录错误
	MOVE_DIR_ERROR, // 3, 移动目录错误
	DELETE_DIR_ERROR, // 4, 删除目录错误
};

template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

struct AVContextWrapper {
	AVIODirContext *ctx {nullptr};
	~AVContextWrapper() {
		avio_close_dir(&ctx);
	}
};
#endif
