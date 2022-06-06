#include "utils/person.hpp"
#include <string>
using std::string;
#include <cstdlib>

int main(void) {
    Person<string, int> p("张三", 21);
    p.showPerson();
    
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}