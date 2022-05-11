#include <iostream>

template <int p, int i=p-1>
class is_prime {
    public:
        // is_prime<(i>2? p: 0), i-1>, 这一步的问号表达式是为了成功走向递归结束条件，
        // 0, 1和 0, 0
        static int constexpr prim = (p==2) || (p%i) && is_prime<(i>2? p: 0), i-1>::prim;
};

// 能够递归到 i=0， 说明是素数了
template <>
class is_prime<0, 0> {
    public:
        static int constexpr prim = 1;
};


// 能够递归到 i = 1，说明也是素数了
template <>
class is_prime<0, 1> {
    public:
        static int constexpr prim = 1;
};


int main(int argc, char* argv[]) {

    std::cout << "is_prime<18>::prim " << is_prime<18>::prim << "\n";
    std::cout << "is_prime<7>::prim " << is_prime<7>::prim << "\n";

    return EXIT_SUCCESS;
}