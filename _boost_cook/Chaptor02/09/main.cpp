#include <boost/scope_exit.hpp>

#include <iostream>

#include <cstdlib>
#include <cstdio>
#include <cassert>

class theres_more_example {
public:
    void close(std::FILE* f) {
        std::fclose(f);
    }

    void theres_more_example_func() {
        std::FILE* f = std::fopen("theres_more_example.txt", "w");
        BOOST_SCOPE_EXIT(f, this_) {
            this_->close(f);
        } BOOST_SCOPE_EXIT_END

        char str[] = "This is the other file\r\n";
        std::fwrite(str, sizeof(str), 1, f);
    }
};

int main(int argc, char* argv[]) {
    std::FILE* f = std::fopen("example_file.txt", "w");
    assert(f);

    // 类似Golang的defer功能
    BOOST_SCOPE_EXIT(f) {
        std::fclose(f);
    } BOOST_SCOPE_EXIT_END

    char str[] = "This is my file\r\n";
    std::fwrite(str, sizeof(str), 1, f);

    theres_more_example example;
    example.theres_more_example_func();
    return 0;
}
