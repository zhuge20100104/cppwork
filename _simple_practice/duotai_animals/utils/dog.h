#ifndef _DOG_H_
#define _DOG_H_

#include "animal.h"

class Dog: public Animal {
    public:
        virtual void Speak();
};
#endif