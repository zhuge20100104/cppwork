#include "utils/manager.h"
#include <ctime>

int main(void) {

    srand((unsigned int)time(nullptr));

    Manager manager;
    manager.setWorkerGroup();
    manager.showWorkerByGroup();

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}