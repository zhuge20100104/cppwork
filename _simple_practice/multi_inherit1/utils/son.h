#ifndef _SON_H_
#define _SON_H_
#include "base1.h"
#include "base2.h"

class Son: public Base1, public Base2 {
    public:
        Son();
    
    private:
        int m_C;
        int m_D;
};
#endif