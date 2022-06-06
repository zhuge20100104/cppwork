#ifndef _FREDRIC_MOMENT_TO_UNDO_HPP_
#define _FREDRIC_MOMENT_TO_UNDO_HPP_

#include <iostream>
#include <memory>
#include <vector>


class BankAccount;
class Momento {
    int balance;
public:
    Momento(int balance_): balance{balance_} {}
    friend class BankAccount;
};

class BankAccount {
    int balance {0};
    std::vector<std::shared_ptr<Momento>> changes;
    int current;

public:
    // 初始化时current设置为0，为最开始的momento
    BankAccount(int const balance_): balance{balance_} {
        changes.emplace_back(std::make_shared<Momento>(balance));
        current = 0;
    }

    std::shared_ptr<Momento> deposit(int amount) {
        balance += amount;
        auto m = std::make_shared<Momento>(balance);
        changes.emplace_back(m);
        ++ current;
        return m;
    }

    // restore相当于在最后加一步
    void restore(std::shared_ptr<Momento> const& m) {
        if(m) {
            balance = m->balance;
            changes.emplace_back(m);
            current = changes.size()-1;
        }
    }


    std::shared_ptr<Momento> undo() {
        if(current > 0) {
            -- current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        return {};
    }

    // redo就是往后走一步
    std::shared_ptr<Momento> redo() {
        if(current + 1 < changes.size()) {
            ++current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        return {};
    }

    friend std::ostream& operator<<(std::ostream& os, BankAccount const& account) {
        os << "balance: " << account.balance;
        return os;
    }
};
#endif