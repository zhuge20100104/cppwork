#include "check.h"

#include <iostream>

Checking::Checking(const std::string& name, float balance, float minBalance): m_MiniumBalance{minBalance},
    Account{name, balance} {
}
Checking::~Checking() {

}


void Checking::WithDraw(float amount) {
    if(m_Balance > 0 && amount > 0 && ((m_Balance-amount) > m_MiniumBalance)) {
        Account::WithDraw(amount);
    } else {
        std::cout << "Invalid amount" << std::endl;
    }
}

float Checking::GetMiniumBalance() const {
    return m_MiniumBalance;
}