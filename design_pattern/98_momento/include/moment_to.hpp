#ifndef _FREDRIC_MOMENT_TO_HPP_
#define _FREDRIC_MOMENT_TO_HPP_

#include <iostream>

class BankAccount;
class Momento {
    int balance;
public:
    Momento(int balance_): balance{balance_} {}
    friend class BankAccount;
};

class BankAccount {
    int balance {0};
public:
    BankAccount(int balance_): balance{balance_} {}

    Momento deposit(int amount) {
        balance += amount;
        return {balance};
    }

    void restore(Momento const& m) {
        balance = m.balance;
    }

    friend std::ostream& operator<<(std::ostream& os, BankAccount const& account) {
        os << "balance: " << account.balance;
        return os;
    }
};



#endif