#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <utility>
#include <unordered_map>
#include <cstdlib>

using std::cout;
using std::endl;
using std::bitset;
using std::string;
using std::unordered_map;
using std::size_t;
using std::pair;
using std::vector;
/*
 * unorder_map自定义key，要定义keyHash和keyEqual仿函数
 * */

struct Key {
    string first;
    string second;
};


struct KeyHash {
    size_t operator()(const Key& key) const {
        return std::hash<string>()(key.first) ^ (std::hash<string>()(key.second) << 1);
    }
};

struct KeyEqual {
    bool operator()(const Key& lhs, const Key& rhs) const {
        return (lhs.first == rhs.first) && (lhs.second == rhs.second);
    }
};

int main(void) {
    unordered_map<string, string> m1;
    unordered_map<int, string> m2 = {{1, "foo"}, {2, "bar"}, {3, "baz"}};
    unordered_map<int, string> m3 = m2;
    unordered_map<int, string> m4 = std::move(m2);
    
    vector<pair<bitset<8>, int> > v = {{0x12 , 1}, {0x01, -1}};
    unordered_map<bitset<8>, double> m5(begin(v), end(v));

    unordered_map<Key, string, KeyHash, KeyEqual> m6 = {{{"John", "Doe"}, "1"},{{"Hello", "World"}, "C++"}};

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}

