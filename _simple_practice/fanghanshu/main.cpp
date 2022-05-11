#include "utils/funcs.h"
#include <stdio.h>

int main() {
    MyPrint print_;
    print_("Hello world");
    MyAdd add;
    int res = add(1, 2);
    cout << "MyAdd(1, 2)= " << res << endl;
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
