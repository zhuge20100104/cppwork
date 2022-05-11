#include "utils/cat.h"
#include "utils/dog.h"

#include <cstdlib>

// 虚函数必须使用父类的指针或者引用实现多态
void TestSpeak(Animal& animal)  {
    animal.Speak();
}

int main(int argc, char* argv[]) {
    
    Dog d;
    TestSpeak(d);
    Cat c;
    TestSpeak(c);

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}