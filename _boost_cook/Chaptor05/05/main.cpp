#include <boost/thread.hpp>

#include <algorithm>
#include <fstream>
#include <iterator>

void set_not_first_run();
bool is_first_run();

// 后台耗时任务
void fill_file_with_data(char fill_char, std::size_t size, const char* filename) {
    std::ofstream ofs(filename);
    std::fill_n(std::ostreambuf_iterator<char>(ofs), size, fill_char);
    set_not_first_run();
}

// 不带线程执行
void example_without_threads() {
    if(is_first_run()) {
        fill_file_with_data('a', 8*1024*1024, "save_file.txt");
    }
}

// 使用线程join方式调度执行
void example_with_join_threads() {
    if(is_first_run()) {
        boost::thread t([]() {
            fill_file_with_data('a', 8*1024*1024, "save_file.txt");
        });

        t.join();
    }
}

int main(int argc, char* argv[]) {
    example_with_join_threads();
}

static bool g_is_first_run = true;

void set_not_first_run() {
    g_is_first_run = false;
}

bool is_first_run() {
    return g_is_first_run;
}
