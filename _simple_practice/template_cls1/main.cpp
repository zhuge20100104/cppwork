#include <iostream>
using std::cout;
using std::endl;

#include <cstdlib>

class Person1 {
    public:
        void showPerson1() {
            cout << "showPerson1" << endl;
        }
};

class Person2 {
    public:
        void showPerson2() {
            cout << "showPerson2" << endl;
        }
};

template <typename T> 
class Showable {

public:
    T person;

    void func1() {
        person.showPerson1();
    }

    void func2() {
        person.showPerson2();
    }
};

int main(void) {

    Showable<Person1> s;
    s.func1();
    // 当需要运行时才参与编译，否则不参与编译
    // s.func2();

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}