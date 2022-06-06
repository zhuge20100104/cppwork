#include "audio_op.h"
#include <iostream>


AudioOp::AudioOp() {
     av_log_set_level(AV_LOG_DEBUG);
     avformat_network_init();
}

AudioOp::~AudioOp() {
     avformat_network_deinit();
}

static const char *type_string(int type)
{
    switch (type) {
    case AVIO_ENTRY_DIRECTORY:
        return "<DIR>";
    case AVIO_ENTRY_FILE:
        return "<FILE>";
    case AVIO_ENTRY_BLOCK_DEVICE:
        return "<BLOCK DEVICE>";
    case AVIO_ENTRY_CHARACTER_DEVICE:
        return "<CHARACTER DEVICE>";
    case AVIO_ENTRY_NAMED_PIPE:
        return "<PIPE>";
    case AVIO_ENTRY_SYMBOLIC_LINK:
        return "<LINK>";
    case AVIO_ENTRY_SOCKET:
        return "<SOCKET>";
    case AVIO_ENTRY_SERVER:
        return "<SERVER>";
    case AVIO_ENTRY_SHARE:
        return "<SHARE>";
    case AVIO_ENTRY_WORKGROUP:
        return "<WORKGROUP>";
    case AVIO_ENTRY_UNKNOWN:
    default:
        break;
    }
    return "<UNKNOWN>";
}

void AudioOp::list_dir(const std::string& dir_name,  FILE_OP_ERRORS& err) {
     AVIODirEntry *entry {nullptr};
     AVContextWrapper ctxWrapper;
     int cnt, ret;
     char filemode[4], uid_and_gid[20];
     if((ret=avio_open_dir(&ctxWrapper.ctx, dir_name.c_str(), nullptr)) < 0) {
          av_log(nullptr, AV_LOG_ERROR, "Can't open directory: %s\n", av_err2str(ret));
          err = FILE_OP_ERRORS::OPEN_DIR_ERROR;
          return;
     }
     cnt = 0;
     for(;;) {
          if((ret=avio_read_dir(ctxWrapper.ctx, &entry)) < 0){
               av_log(nullptr, AV_LOG_ERROR, "Cannot list directory: %s.\n", av_err2str(ret));
               err = FILE_OP_ERRORS::READ_DIR_ERROR;
               return;
          }
          if(!entry) {
               break;
          }
          // 未知的文件模式
          if(entry->filemode == -1) {
               snprintf(filemode, 4, "???");
          }else {
               // 以8进制输出int64整数
               snprintf(filemode, 4, "%3" PRIo64, entry->filemode);
          }
          // 以10进制输出uid和gid，中间用%分隔
          snprintf(uid_and_gid, 20, "%" PRId64 "(%" PRId64 ")", entry->user_id, entry->group_id);
          // 第一次，打印表头
          if (cnt == 0)
            av_log(NULL, AV_LOG_INFO, "%-9s %12s %30s %10s %s %16s %16s %16s\n",
                   "TYPE", "SIZE", "NAME", "UID(GID)", "UGO", "MODIFIED",
                   "ACCESSED", "STATUS_CHANGED");
          av_log(nullptr, AV_LOG_INFO, "%-9s %12" PRId64 " %30s %10s %s %16" PRId64 " %16" PRId64 " %16" PRId64 "\n",
               type_string(entry->type),
               entry->size,
               entry->name,
               uid_and_gid,
               filemode,
               entry->modification_timestamp,
               entry->access_timestamp,
               entry->status_change_timestamp);
          avio_free_directory_entry(&entry);
          cnt++;
     }

}

void AudioOp::move_dir(const std::string& src, const std::string& dst,  FILE_OP_ERRORS& err){
     int ret = avpriv_io_move(src.c_str(), dst.c_str());
     if (ret < 0){
        av_log(NULL, AV_LOG_ERROR, "Cannot move '%s' into '%s': %s.\n", src.c_str(), dst.c_str(), av_err2str(ret));
        err = FILE_OP_ERRORS::MOVE_DIR_ERROR;
     }
}

void AudioOp::delete_dir(const std::string& src,  FILE_OP_ERRORS& err){
     int ret = avpriv_io_delete(src.c_str());
     if (ret < 0){
          av_log(NULL, AV_LOG_ERROR, "Cannot delete '%s': %s.\n", src.c_str(), av_err2str(ret));
          err = FILE_OP_ERRORS::DELETE_DIR_ERROR;
     }      
}