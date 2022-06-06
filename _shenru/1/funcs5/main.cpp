#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::function;
using std::bind;
using std::placeholders::_1;
using std::placeholders::_2;
#include <cstdlib>

void output(int x, int y) {
    cout << x << " " << y << " " << endl;
}


int main(void) {
    bind(output, 1, 2)();
    bind(output, _1, 2) (1);
    bind(output, 2, _1)(1);
    bind(output, 2, _2)(1,2);
    bind(output, _1, _2) (1, 2);
    bind(output, _2, _1) (1, 2);
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
