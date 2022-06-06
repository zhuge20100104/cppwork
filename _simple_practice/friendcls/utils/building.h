#ifndef _BUILDING_H_
#define _BUILDING_H_
#include <iostream>
using std::string;

class Building {
    friend class GoodGay;
public:
    Building();
    string mSittingRoom; // 客厅

private:
    string mBedRoom; // 卧室
};
#endif