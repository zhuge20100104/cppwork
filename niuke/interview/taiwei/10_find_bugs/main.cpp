#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;


int main(int argc, char* argv[]) {
	int n;
    // 1. argv[0]是char*类型，需要用std::atoi转换成int
    // 2. 获取的参数值应该是第1个参数，不是第0个参数，第0个参数是 exe 或者elf文件名
    // 3. delete [] stuff是个arr，应该使用[]删除法
    // 4. 如果 argc < 1, 说明没传count参数，应该return
	if(argc > 1){ 
        n = atoi(argv[1]); 
    } else { 
        return EXIT_FAILURE;
    }

	cout << n << endl;
	int* stuff = new int[n];
	vector<int> v(10000);
	delete [] stuff;
    return EXIT_SUCCESS;
}