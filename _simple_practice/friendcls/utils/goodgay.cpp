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
    cout << "好基友正在访问: " << this->building->mSittingRoom << endl;
    cout << "好基友正在访问: " << this->building->mBedRoom << endl;
}
