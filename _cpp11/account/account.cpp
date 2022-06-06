#include "account.h"

#include <iostream>

// 账号生成器
int Account::m_ANGenerator = 1000;

Account::Account(const std::string& name, float balance): m_Name{name}, m_Balance{balance} {
    m_AccNo = ++m_ANGenerator;
    std::cout << "Account::Account(const std::string& name, float balance)" << std::endl;
}

Account::~Account() {
    std::cout << "Account::~Account()" << std::endl;
}

const std::string Account::GetName() const {
    return m_Name;
}

int Account::GetAccountNo() const {
    return m_AccNo;
}

float Account::GetBalance() const {
    return m_Balance;
}

void Account::Deposit(float amount) {
    m_Balance += amount;
}

void Account::WithDraw(float amount) {
    if(amount < m_Balance && m_Balance > 0) {
        m_Balance -= amount;
    } else {
        throw std::runtime_error("insufficient balance");
    }
}

float Account::GetInterestRate() const {
    return 0.0f;
}

void Account::AccumulateInterest() {

}

