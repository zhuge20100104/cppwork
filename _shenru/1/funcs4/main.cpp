#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::function;
using std::placeholders::_1;

#include <cstdlib>

void call_when_even(int x, const function<void(int)>& f) {
    if(!(x&1)){ // x%2 == 0
        f(x);
    }
}

void output(int x) {
    cout << x << " ";
}

void output_add_2(int x) {
    cout << x + 2 << " ";
} 

int main(void) {
    {
        auto fr = std::bind(output, _1);
        for(int i=0; i<10; i++) {
            call_when_even(i, fr);
        }
        cout << endl;
    }

    {
        auto fr = std::bind(output_add_2, _1);
        for(int i=0; i<10; i++) {
            call_when_even(i, fr);
        }
        cout << endl;
    }

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}


