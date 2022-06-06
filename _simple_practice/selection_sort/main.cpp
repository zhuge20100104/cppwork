#include <iostream>

#include <algorithm>

void sort(int arr[10], int length) {

    for(int i = 0; i<length; i++) {
        for(int j=i+1; j<length; j++) {
            if(arr[i]>arr[j]) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

int main() {
    int arr[10] = {10, 8, 7, 9, 5, 4, 3, 6, 1, 2};

    sort(arr, sizeof(arr)/sizeof(int));

    // 打印
    std::for_each(std::begin(arr), std::end(arr), [](const int& i) {
        std::cout << i << " ";
    });
    std::cout << std::endl;
}