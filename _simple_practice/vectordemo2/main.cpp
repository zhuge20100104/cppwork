#include <iostream>
using std::cout;
using std::endl;
#include <vector>

#include <cstdlib>
using std::vector;

#include <algorithm>

using std::for_each;

using intvec = vector<int>;
using intvecvec =  vector<vector<int> >;
using intvec_it = intvec::iterator;
using intvecvec_it = intvecvec::iterator;

int main(void) {

    intvecvec v;
    intvec v1;
    intvec v2;
    intvec v3;
    intvec v4;

    for(int i=0; i<4; i++) {
        v1.push_back(i+1);
        v2.push_back(i+2);
        v3.push_back(i+3);
        v4.push_back(i+4);
    }

    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);

    for(intvecvec_it itout = v.begin(), itoute = v.end(); itout != itoute; ++itout) {
        for(intvec_it it = itout->begin(), ite = itout->end(); it != ite; ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }
    
    cout << "-------------------------------------------------------" << endl;

    for_each(v.begin(), v.end(), [](const intvec& it ) {
        for_each(it.begin(), it.end(), [](const int& val) {
            cout << val << " ";
        });
        cout << endl;
    });

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}