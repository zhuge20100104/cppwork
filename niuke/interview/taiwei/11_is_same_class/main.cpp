#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

// 思路照抄 C++11 标准库 std::is_same<class T, class U>实现即可
// 普通类模板，两者类型不同，返回std::false_type
using namespace std;
template<typename, typename>
    struct is_same_class
    : public false_type { };


// 模板特化，两者类型相同，返回std::true_type
template<typename _Tp>
struct is_same_class<_Tp, _Tp>: public true_type { };

struct A {};


int main(int argc, char* argv[]) {
	cout << std::boolalpha << is_same_class<A, A>::value << endl; 
    return EXIT_SUCCESS;
}