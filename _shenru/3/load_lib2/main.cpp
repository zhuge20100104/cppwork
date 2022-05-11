#include "dll_parser.hpp"
#include <cstdlib>

void TestDllParser() {
    DLLParser parser;
    string s = "mydll.dll";
    // 加载 dll
    parser.Load(s);

    int a = 5;
    int b = 8;

    auto max = parser.ExecuteFunc<int(const int&, const int&)>("Max", a , b);
    cout << "Max(5, 8): " << max << endl;

    a = 7;
    b = 3;
    max = parser.ExecuteFunc<int(const int&, const int&)>("Max", a, b);
    cout << "Max(7, 3): " << max << endl;

    auto add = parser.ExecuteFunc<int(int&, int&)>("Add", a, b);
    cout << "Add(7, 3): " << add << endl;
}

int main(void) {
    TestDllParser();

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}