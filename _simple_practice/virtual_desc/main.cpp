#include "utils/cat.h"

#include <cstdlib>

using AnimalPtr = std::shared_ptr<Animal>;

void TestVirtualDesc() {
    AnimalPtr cat(new Cat("Tom"));
    cat->Speak();
}

int main(int argc, char* argv[]) {
    TestVirtualDesc();
    
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
