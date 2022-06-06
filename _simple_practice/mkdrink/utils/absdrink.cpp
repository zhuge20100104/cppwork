#include "absdrink.h"

void AbsDrink::MakeDrink() {
    this->Boil();
    this->Brew();
    this->PourInCup();
    this->PutSomething();
}