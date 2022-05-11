#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;
#include <utility>
#include <cstdlib>

class CountEven {
    int& count_;

    public:
        CountEven(int& count): count_(count) {
        }

        void operator()(int val) {
            if(!(val&1)) { // x%2 ==0
                count_++;
            }
        }
};


int main(void) {
    vector<int> v = {1, 2, 3, 4, 5, 6};
    int event_count = 0;

    std::for_each(begin(v), end(v), CountEven(event_count));
    cout << "偶数的个数是: " << event_count << endl;
    
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
