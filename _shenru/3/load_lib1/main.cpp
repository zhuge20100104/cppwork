#include "mydll.h"

#include <iostream>
using std::cout;
using std::endl;

#include <windows.h>
#include <cstdlib>

void TestDLL() {
    using pMax = int (*)(const int &a, const int &b);
    using pGet = int (*)(const int &a);

    HINSTANCE hDll = LoadLibrary(LPCTSTR("mydll.dll"));
    if(hDll == nullptr) {
        cout << "hDll load failed..." << endl;
        return;
    }

    pMax Max = reinterpret_cast<pMax>(GetProcAddress(hDll, "Max")); 
    if(Max == nullptr) {
        cout << "Load Max function failed..." << endl;
        return;
    }

    int ret = Max(5, 8);
    cout << "Max(5, 8): " << ret << endl;

    pGet Get = reinterpret_cast<pGet>(GetProcAddress(hDll, "Get"));
    if(Get == nullptr) {
        cout << "Load Get function failed..." << endl;
        return;
    }

    int ret2 = Get(5);
    cout << "Get(5): " << ret2 << endl;

    FreeLibrary(hDll);
}

int main(void) {
    TestDLL();
    
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}