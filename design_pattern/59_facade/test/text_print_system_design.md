# Text Print System Design

## 最大宽度 和 最大高度 
## 取最大宽度 为宽度，取最大高度为高度
## 每次绘制先往下加(最大高度 + 2)，接着画
## Window的宽度为最大宽度
## Window的高度为 行数 * (最大高度  + 2)

## CPP Code Demo
```
struct TextBuffer {
    std::vector<std::string> texts;
    double max_width;
    double max_height;
    double total_height;

    void add_string() {
        // update max_width
        // update_max_height
        // update total_height
    }
};

struct Window {
    std::vector<TextBuffer> buffers;
    
    void add_buffer() {
        
    }

    void show() {
        // 获取所有buffer的最大宽，作为窗口宽
        // 获取所有buffer的高之和，作为窗口高
        // 从上往下显示buffer
        // 第0个: 0, 0
        // 第1个: 1, buffer0.total_height
        // 第2个: 2, buffer0.total_height + buffer1.total_height
    }

private:
    int width;
    int height;
    int get_width() {
        // std::max  buffer0.max_width, buffer1.max_width, buffer2.max_width ... buffern.max_width
        return result;
    }

    int get_height() {
        // std::accumulate buffer0.total_height, buffer1.total_height, buffer2.total_height ... buffern.total_height
        return result;
    }
};
```

