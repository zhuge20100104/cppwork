#ifndef _BUILDING_H_
#define _BUILDING_H_
#include "goodgay.h"
#include <string>

using std::string;
class Building {
    friend void GoodGay::visit();
    public:
        Building();
    
        string mSittingRoom;

    private:
        string mBedRoom;
};
#endif
