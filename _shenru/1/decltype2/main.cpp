#include <iostream>
#include <vector>
#include <cstdio>

using std::vector;
using std::cout;
using std::endl;



template <class ContainerT>
class Foo {
    decltype(std::declval<ContainerT>().begin()) _it;

    public:
        void func(ContainerT& container) {
            _it = container.begin();
            for(; _it!=container.end(); ++_it) {
                cout << *_it << " ";
            }
            cout << endl;
        }
};


int main() {
    using containert_ = const vector<int>;
    containert_ v = {1, 2, 3, 4, 5};
    Foo<containert_>  foo;
    foo.func(v);

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
