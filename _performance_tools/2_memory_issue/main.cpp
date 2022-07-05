#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    string* s1 = new string("Hello world!");
    cout << *s1 << endl;

    int a[2] = {1, 0};
    int b = a[2];
    return EXIT_SUCCESS;
}