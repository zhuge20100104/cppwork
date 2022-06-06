#include "utils/cal.h"

#include <iostream>
using std::cout;
using std::endl;
#include <cstdlib>
#include <memory>
using std::shared_ptr;

int main(int argc, char* argv[]) {

    shared_ptr<AbsCal> cal(new AddCal);
    cal->m_Num1 = 10;
    cal->m_Num2 = 8;

    cout << "10 + 8 = " << cal->getResult() << endl;
    
    shared_ptr<AbsCal> calSub(new SubCal);
    calSub->m_Num1 = 10;
    calSub->m_Num2 = 8;
    cout << "10 - 8 = " << calSub->getResult() << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}