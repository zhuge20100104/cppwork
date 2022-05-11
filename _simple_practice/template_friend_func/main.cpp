#include "utils/person.hpp"
#include <cstdlib>
#include <string>
using std::string;

int main(void) {

    Person<string, int> p("张三", 23);
    PrintPerson(p);
    cout << "------------------------------------------" << endl;
    PrintPerson2(p);

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}