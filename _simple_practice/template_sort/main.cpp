#include <iostream>
#include <algorithm>
#include <vector>

using std::cout;
using std::endl;
using std::for_each;
using std::begin;
using std::end;

// 输出当前数组元素的lambda表达式宏
#define OUT_T(type, ele)  [](const type &ele) { \
        cout << ele; \
    }

// 获取元素大小的宏 eles数组，ele_type类型
#define SIZE(eles, ele_type)  sizeof(eles)/sizeof(ele_type)

template <typename T>
void MySwap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T>
void MySort(T arr[], int size) {
    for(int i = 0; i<size; i++) {
        T max = i;
        for(int j=i+1; j<size; j++) {
            if(arr[max] < arr[j]) {
                max = j;
            }
        }

        if(max != i) {
            MySwap(arr[max], arr[i]);
        }
    }
}


int main() {
    char eles[] = "abced";
    
    cout << "排序前:" << endl;
    for_each(begin(eles), end(eles), OUT_T(char, ele));
    cout << endl;

    MySort(eles, SIZE(eles, char));
    cout << "排序后:" << endl;
    for_each(begin(eles), end(eles), OUT_T(char, ele));
    cout << endl;

    cout << "-------------------------------------------" << endl;

    int ints[] = {1, 3, 2, 4, 5, 7, 6, 8, 9};
    cout << "排序前:" << endl;
    for_each(begin(ints), end(ints), OUT_T(int, ele));
    cout << endl;

    MySort(ints, SIZE(ints, int));
    cout << "排序后:" << endl;
    for_each(begin(ints), end(ints), OUT_T(int, ele));
    cout << endl;
} 