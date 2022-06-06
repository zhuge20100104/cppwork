#include <iostream>

namespace Avg {
    float calculate(float x, float y) {
        return (x + y) / 2;
    }
};

namespace Basic { 
    float calculate(float x, float y) {
        return x + y;
    }
}; // namespace Basic


// 名称空间嵌套
namespace Compare {
    namespace Sort {
        bool less(int x, int y) {
            return x < y;
        }
    };
};

// 匿名名称空间，只在本文件可用
namespace {
    void internal_func() {
        std::cout << "internal_func()" << std::endl;
    }
};

int main(int argc, char* argv[]) {
    auto res = Avg::calculate(3.0f, 6.0f);
    std::cout << "Avg::calculate(3.0f, 6.0f) = " << res << std::endl;

    res = Basic::calculate(3.0f, 5.0f);
    std::cout << "Basic::calculate(3.0f + 5.0f) = " << res << std::endl;

    auto is_less = Compare::Sort::less(3, 5);
    std::cout << "Compare::Sort::less(3, 5) = " << is_less << std::endl;

    ::internal_func();
}