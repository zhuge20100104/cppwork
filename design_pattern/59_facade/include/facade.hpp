#ifndef _FREDRIC_FACADE_HPP_
#define _FREDRIC_FACADE_HPP_

#include "window.h"
#include <memory>

class Console {
public:
    static Console& instance() {
        static Console console;
        return console;
    }

    std::shared_ptr<Window> single_buffers(int buffer_count) {
        auto w = std::make_shared<Window>();
        w->add_buffer(TextBuffer{});
        return w;
    }

    std::shared_ptr<Window> multi_buffers(int buffer_count) {
        auto w = std::make_shared<Window>();
        for(int i=0; i<buffer_count; ++i) {
            w->add_buffer(TextBuffer{});
        }
        return w;
    }
};

#endif