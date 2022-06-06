#ifndef _UTILS_H_
#define _UTILS_H_

#include <memory>

// 初始化特定类型文件指针的宏, stream_type是流类型，f是流变量
#define INIT_FILE_PTR(stream_type, f)  std::shared_ptr<stream_type> f(new stream_type, [](stream_type* f){ \
        f->close(); \
        delete f; \
        f = nullptr; \
    })

#endif