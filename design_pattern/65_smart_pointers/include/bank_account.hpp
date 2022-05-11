#ifndef _FREDRIC_BANK_ACCOUNT_HPP_
#define _FREDRIC_BANK_ACCOUNT_HPP_

#include <string>
#include <iostream>
#include <vector>

struct BankAccount {
    virtual ~BankAccount() = default;

    virtual void deposit(int amount) = 0;
    virtual void withdraw(int amount) = 0;
};

struct CurrentAccount: BankAccount {
    explicit CurrentAccount(int const balance_): balance{balance_} {}
    void deposit(int amount) override {
        balance += amount;
    }

    void withdraw(int amount) override {
        if(amount <= balance)
            balance -= amount;
    }

    friend std::ostream& operator<<(std::ostream& os, CurrentAccount const& obj) {
        os << "balance: " << obj.balance;
        return os;
    }

private:
    int balance;
};



#endif