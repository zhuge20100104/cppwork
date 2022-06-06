#include "utils/objs.h"
#include <memory>
using std::shared_ptr;

#include <cstdlib>

int main(int argc, char* argv[]) {
    shared_ptr<Base> b(new Son);
    b->func();
    
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}