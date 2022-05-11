#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>

using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::string;
using std::make_pair;

struct Complicated {
    int year;
    double country;
    string name;

    Complicated(int a, double b, string c): year(a), country(b), name(c)  {
        cout << "is contructed" << endl;
    }

    Complicated(const Complicated& other): year(other.year), country(other.country), name(std::move(other.name)) {
        cout << "is moved" << endl;
    }

};

int main(void) {
    map<int, Complicated> m;
    int anInt = 4;
    double aDouble = 5.0;
    string aString = "C++";

    cout << "Insert -----" << endl;
    m.insert(make_pair(4, Complicated(anInt, aDouble, aString)));
    
    cout << "Emplace ----" << endl;
    m.emplace(4, Complicated(anInt, aDouble, aString));
    
    vector<Complicated> v;
    cout << "Emplace Back ---" << endl;
    v.emplace_back(anInt, aDouble, aString);

    cout << "Push Back ----" << endl;
    v.push_back(Complicated(anInt, aDouble, aString));

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
