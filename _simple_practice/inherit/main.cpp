#include "utils/python.h"
#include "utils/java.h"
#include "utils/cpp.h"
#include <stdio.h>

int main() {
    BasePage* p = new Python;
    p->header();
    p->footer();
    p->lefter();
    p->content();
    delete p;
    p = NULL;
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
