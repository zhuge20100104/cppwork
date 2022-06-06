#include "utils/array.hpp"
using utils::Array;
#include <cstdlib>

#include <algorithm>
#include <vector>
using std::for_each;

int main(void) {
    Array<int> arr(10);
    arr.push_back(9);
    arr.push_back(8);
    arr.push_back(7);

    cout << "arr的数值打印: " << endl; 
    for(int i=0; i<arr.getSize(); i++) {
        cout << arr[i] << " ";    
    }
    cout << endl;

    Array<int> arr2 = arr;
    cout << "arr2的数值打印: " << endl; 
    for(int i=0; i<arr2.getSize(); i++) {
        cout << arr2[i] << " ";    
    }
    cout << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}