#ifndef _SON_H_
#define _SON_H_

#include "base1.h"
#include "base2.h"


class Son: public Base1, public Base2 {
    public:
        int mC;
        int mD;

        Son() {
            mC = 300;
            mD = 400;
        }
};
#endif
