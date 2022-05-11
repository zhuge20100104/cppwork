#include "media_info.h"
#include <iostream>

MediaInfo::MediaInfo(const std::string& src_file_name): filename_(src_file_name) {
     av_register_all();

     MediaOpErrors err = MediaOpErrors::NO_ERROR;
     init(err);
     if(err != MediaOpErrors::NO_ERROR) {
          throw MediaOpenExcept();
     }
}


void MediaInfo::init(MediaOpErrors& err) {
     int err_code = 0;
     char errors[1024];
     if((err_code = avformat_open_input(&fmt_ctx, filename_.c_str(), nullptr, nullptr)) < 0) {
          av_strerror(err_code, errors, 1024);
          std::cerr << "Could not open source file: " << filename_ << " ," 
               << err_code << "(" << errors << ")"
               << std::endl;
          err = MediaOpErrors::OPEN_MEDIA_ERROR;
          return;
     }

     if((err_code = avformat_find_stream_info(fmt_ctx, nullptr)) < 0) {
          av_strerror(err_code, errors, 1024);
          std::cerr << "Could not find stream info: " << filename_ << " ,"
               << err_code << "(" << errors << ")"
               << std::endl;
          err = MediaOpErrors::FIND_STREAM_ERROR; 
     }
}



MediaInfo::~MediaInfo() {
     // 关闭输入文件
     avformat_close_input(&fmt_ctx);
}

void MediaInfo::printInfo() {
     av_dump_format(fmt_ctx, 0, filename_.c_str(), 0);
}