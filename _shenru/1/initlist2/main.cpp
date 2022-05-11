#include <iostream>

using std::cout;
using std::endl;
using std::initializer_list;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include <cstdio>

class FooVector {
    vector<int> content_;
    
    public:
        FooVector(initializer_list<int> l) {
            for(auto it=l.begin(); it!=l.end(); ++it) {
                content_.emplace_back(*it);
            }
        }

};

class FooMap {
    map<int, int> content_;
    using pair_t = map<int,int>::value_type;
    public:
        FooMap(initializer_list<pair_t> l) {
            for(auto it=l.begin(); it!=l.end(); ++it) {
                content_.emplace(*it);
            }
        } 
};


int main() {
    FooVector fooVector {1, 2, 3, 4, 5};
    FooMap fooMap {{1,2}, {3, 4}, {5, 6}};
    
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}

