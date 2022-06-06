#include <iostream>
using std::cout;
using std::endl;
#include <tuple>
#include <cstdlib>

template <typename Tuple, std::size_t N>
struct TuplePrinter {
    static void print(const Tuple& t) {
        // 递归调用第  N - 1个的print，打印剩余元素
        TuplePrinter<Tuple, N - 1>::print(t);
        // 打印第 N - 1个元素
        cout << "," << std::get<N-1>(t);
    }
};

// 递归终止模板
template <class Tuple>
struct TuplePrinter<Tuple, 1> {
    static void print(const Tuple& t) {
        // 打印最后一个元素
        cout << std::get<0>(t);
    }
};


// 提供一个打印函数来封装模板类
template <typename... Args>
void PrintTuple(const std::tuple<Args...>& t) {
    cout << "(";
    TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
    cout << ")";
    cout << endl;
}


int main(void) {
    std::tuple<int, short, double, char>  tp = std::make_tuple(1, 2, 3, 'a');
    PrintTuple(tp);

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}

