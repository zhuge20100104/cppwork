#include "audio_op.h"
#include <iostream>


AudioOp::AudioOp() {
     av_log_set_level(AV_LOG_DEBUG);
     av_register_all();
}

AudioOp::~AudioOp() {
}

// 根据包大小，构造ADTS header的函数
// ADTS header详细信息请参考 https://www.jianshu.com/p/b5ca697535bd
void AudioOp::adts_header(char* szAdtsHeader, int dataLen) {
    // 不同视频的音频流参数可能不一样
    int audio_object_type = 2;  // 2是aac LC
    int sampling_frequency_index = 4;  // 采样频率 44100是0x4
    int channel_config = 2; // stero是双声道，左声道+右声道

    int adtsLen = dataLen + 7;

    szAdtsHeader[0] = 0xff;         //syncword:0xfff                          高8bits
    szAdtsHeader[1] = 0xf0;         //syncword:0xfff                          低4bits
    szAdtsHeader[1] |= (0 << 3);    //MPEG Version:0 for MPEG-4,1 for MPEG-2  1bit
    szAdtsHeader[1] |= (0 << 1);    //Layer:0                                 2bits 
    szAdtsHeader[1] |= 1;           //protection absent:1                     1bit

    szAdtsHeader[2] = (audio_object_type - 1)<<6;            //profile:audio_object_type - 1                      2bits
    szAdtsHeader[2] |= (sampling_frequency_index & 0x0f)<<2; //sampling frequency index:sampling_frequency_index  4bits 
    szAdtsHeader[2] |= (0 << 1);                             //private bit:0                                      1bit
    szAdtsHeader[2] |= (channel_config & 0x04)>>2;           //channel configuration:channel_config               高1bit

    szAdtsHeader[3] = (channel_config & 0x03)<<6;     //channel configuration:channel_config      低2bits
    szAdtsHeader[3] |= (0 << 5);                      //original：0                               1bit
    szAdtsHeader[3] |= (0 << 4);                      //home：0                                   1bit
    szAdtsHeader[3] |= (0 << 3);                      //copyright id bit：0                       1bit  
    szAdtsHeader[3] |= (0 << 2);                      //copyright id start：0                     1bit
    szAdtsHeader[3] |= ((adtsLen & 0x1800) >> 11);           //frame length：value   高2bits

    szAdtsHeader[4] = (uint8_t)((adtsLen & 0x7f8) >> 3);     //frame length:value    中间8bits
    szAdtsHeader[5] = (uint8_t)((adtsLen & 0x7) << 5);       //frame length:value    低3bits
    szAdtsHeader[5] |= 0x1f;                                 //buffer fullness:0x7ff 高5bits
    szAdtsHeader[6] = 0xfc;
}

void AudioOp::extract_audio(const std::string& src_video, const std::string& dst_audio, 
        AUDIO_OP_ERRORS& err) {
     
     AudioOpWrapper op_wrapper;
     int err_code = 0;
     char errors[1024];

     // 打开输出文件
     op_wrapper.dst_fd = fopen(dst_audio.c_str(), "wb");
     if(!op_wrapper.dst_fd) {
          av_log(nullptr, AV_LOG_DEBUG, "Could not open destination file %s\n", dst_audio.c_str());
          err = AUDIO_OP_ERRORS::OPEN_FILE_ERROR;
          return;
     }
     // 打开输入的视频文件，分配文件操作上下文
     if((err_code = avformat_open_input(&op_wrapper.fmt_ctx, src_video.c_str(), nullptr, nullptr)) < 0) {
          av_strerror(err_code, errors, 1024);
          av_log(nullptr, AV_LOG_DEBUG, "Could not open source file: %s, %d(%s)\n", 
               src_video.c_str(),
               err_code,
               errors);
          err = AUDIO_OP_ERRORS::OPEN_INPUT_VIDEO_ERROR;
          return;
     }

     // 查找流信息
     if((err_code = avformat_find_stream_info(op_wrapper.fmt_ctx, nullptr)) < 0) {
          av_strerror(err_code, errors, 1024);
          av_log(NULL, AV_LOG_DEBUG, "failed to find stream information: %s, %d(%s)\n",
               src_video.c_str(),
               err_code,
               errors);

          err = AUDIO_OP_ERRORS::FIND_STREAM_ERROR;
          return;
     }

     // 显示视频流信息
     av_dump_format(op_wrapper.fmt_ctx, 0, src_video.c_str(), 0);

     // 初始化音频流解析包
     av_init_packet(&op_wrapper.pkt);
     op_wrapper.pkt.data = nullptr;
     op_wrapper.pkt.size = 0;

     // 查找最好的音频流
     int audio_stream_index = av_find_best_stream(op_wrapper.fmt_ctx, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
     if(audio_stream_index < 0) {
          av_log(NULL, AV_LOG_DEBUG, "Could not find %s stream in input file %s\n",
               av_get_media_type_string(AVMEDIA_TYPE_AUDIO),
               src_video.c_str());
          err = AUDIO_OP_ERRORS::FIND_AUDIO_ERROR;
          return;
     } 

     int len = 0;
     // 逐个包读取，加上adts头，然后写入目标文件
     while((av_read_frame(op_wrapper.fmt_ctx, &op_wrapper.pkt)) >= 0) {
          // 刚好是音频流
          if(op_wrapper.pkt.stream_index == audio_stream_index) {
               char adts_header_buf[7];
               adts_header(adts_header_buf, op_wrapper.pkt.size);
               fwrite(adts_header_buf, 1, 7, op_wrapper.dst_fd);
               len = fwrite(op_wrapper.pkt.data, 1, op_wrapper.pkt.size, op_wrapper.dst_fd); 
               if(len != op_wrapper.pkt.size) {
                    av_log(NULL, AV_LOG_DEBUG, "warning, length of writed data isn't equal pkt.size(%d, %d)\n",
                       len,
                       op_wrapper.pkt.size);
               }
          }
     }
}

