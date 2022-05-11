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


enum class AUDIO_OP_ERRORS {
  	NO_ERROR,   // 0， 无错误
	OPEN_FILE_ERROR, // 1, 打开文件错误
	OPEN_INPUT_VIDEO_ERROR, // 2, 打开输入的视频文件出错
	FIND_STREAM_ERROR, // 3, 查找流信息失败错误
	FIND_AUDIO_ERROR, // 4, 查找音频流失败
};

template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

struct AudioOpWrapper {
	// 输出文件句柄
	FILE *dst_fd {nullptr};
	// 输入文件格式
	AVFormatContext* fmt_ctx {nullptr};
	// 每次读取的音频包
	AVPacket pkt{};

	~AudioOpWrapper() {
		if(pkt.buf != nullptr) {
			av_packet_unref(&pkt);
		}
		if(dst_fd) {
			fclose(dst_fd);
		} 
		if(fmt_ctx) {
			avformat_close_input(&fmt_ctx);
		}
	}
};
#endif
