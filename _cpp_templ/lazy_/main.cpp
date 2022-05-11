#include <iostream>
#include <cstdlib>

template <typename T>
class Safe {};

template <int N>
class Danger {
    public:
        typedef char Block[N];  // N 应该大于等于0，否则会挂
};

template <typename T, int N>
class Tricy {
    public:
        virtual ~Tricy() {}
    
        void no_body_here(Safe<T> = 3);

        void in_class() {
            Danger<N> no_boom_yet;
            // typename Danger<N>::Block block_;
        }

        T operator->();

        struct Nested {
            Danger<N> pfew;
        };

        union {
            int align;
            Safe<T> anonymous;
        };
};


// C++ 新标准，允许零长数组
int main(int argc, char* argv[]) {
    Tricy<int, -1> ok;
    ok.in_class();
    return EXIT_SUCCESS;
}
