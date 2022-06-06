#include <iostream>
#include <cstdlib>

template <typename T>
inline T const& max(T const& a, T const& b) {
    return a < b ? b : a;
}

int main(int argc, char* argv[]) {
    auto res = max<double>(1.0, 3.0); //显示指定
    std::cout << "max<double>(1.0, 3.0)=" << res << std::endl;

    auto res1 = max(1.0, -3.0);  // 模板参数推导
    std::cout << "max(1.0, -3.0)=" << res1 << std::endl;

    auto res2 = max<int>(1.0, 3.0);  // 显示指定为int
    std::cout << "max<int>(1.0, 3.0)=" << res2 << std::endl;
    return EXIT_SUCCESS;
}