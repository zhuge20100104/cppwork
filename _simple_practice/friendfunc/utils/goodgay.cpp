#include "goodgay.h"
#include "building.h"

GoodGay::GoodGay() {
    this->building = new Building;
}

GoodGay::~GoodGay() {
    if(this->building != NULL) {
        delete this->building;
        this->building = NULL;
    }
} 


void GoodGay::visit() {
    cout << "visit函数正在访问" << building->mSittingRoom << endl;
    cout << "visit函数正在访问" << building->mBedRoom << endl;
}
