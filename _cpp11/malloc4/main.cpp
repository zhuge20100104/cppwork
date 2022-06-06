#include <iostream>
#include <cstdlib>

void test_2_dimension_arr() {
    int** arr = new int*[2];
    for(int i=0; i<2; ++i) {
        arr[i] = new int[3];
    }

    for(int i=0; i<2; ++i) {
        for(int j=0; j<3; ++j) {
            arr[i][j] = i+j;
        }
    }

    for(int i=0; i<2; ++i) {
        for(int j=0; j<3; ++j) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    for(int i=0; i<2; ++i) {
        delete [] arr[i];
    }

    delete [] arr;
}

int main(int argc, char* argv[]) {
    test_2_dimension_arr();
    return EXIT_SUCCESS;
}