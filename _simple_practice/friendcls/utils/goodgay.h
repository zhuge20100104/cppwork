#ifndef _GOOD_GAY_H_
#define _GOOD_GAY_H
#include <iostream>
using std::cout;
using std::endl;

class Building;
class GoodGay {
public:
    GoodGay();
    ~GoodGay();
    void visit();

private:
    Building* building;
};
#endif