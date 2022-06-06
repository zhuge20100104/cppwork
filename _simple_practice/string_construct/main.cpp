#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <cstdlib>


int main(void) {

    const char* str = "Hello";
    string s(str);
    string s2 = s;
    string s3(10, 'a');

    cout << "str=" << str << endl;
    cout << "s=" << s << endl;
    cout << "s2=" << s2 << endl;
    cout << "s3=" << s3 << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}