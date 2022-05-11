#ifndef _FREDRIC_COMPOSITE_CMD_HPP_
#define _FREDRIC_COMPOSITE_CMD_HPP_

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

struct BankAccount {
    int balance{0};
    int overdraft_limit{-500};

    void deposit(int amount) {
        balance += amount;
        std::cout << "deposited " << amount << ", balance is now: " << balance
                  << std::endl;
    }

    // 取款可能失败，添加标志位
    bool withdraw(int amount) {
        if (balance - amount >= overdraft_limit) {
            balance -= amount;
            std::cout << "withdrew " << amount
                      << ", balance is now: " << balance << std::endl;
            return true;
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, BankAccount const& account) {
        os << "balance: " << account.balance;
        return os;
    }
};

struct Command {
    virtual void call() = 0;
    virtual void undo() = 0;
};

struct BankAccountCommand : Command {
    bool succeeded {false};
    BankAccount& account;
    enum Action { deposit, withdraw } action;
    int amount;

    BankAccountCommand(BankAccount& account_, Action action_, int amount_)
        : account{account_}, action{action_}, amount{amount_} {}

    void call() override {
        switch (action) {
            case deposit:
                account.deposit(amount);
                succeeded = true;
                break;
            case withdraw:
                succeeded = account.withdraw(amount);
                break;
        }
    }

    void undo() override {
        // 操作失败，不做undo
        if(!succeeded) {
            return;
        }

        switch (action)
        {
        case deposit:
            account.withdraw(amount);
            break;
        
        case withdraw:
            account.deposit(amount);
            break;
        }
    }
};

struct CompositeBankAccountCommand: Command {
    std::vector<BankAccountCommand> cmds{};
    CompositeBankAccountCommand(std::initializer_list<BankAccountCommand> const& items): cmds{items} {}

    void call() override {
        bool ok {true};
        for(auto&& cmd: cmds) {
            if(ok) {
                cmd.call();
                ok = cmd.succeeded;
            }else {
                cmd.succeeded = false;
            } 
        }
    }

    void undo() override {
        for(auto&& cmd_it = cmds.rbegin(); cmd_it != cmds.rend(); ++cmd_it) {
            cmd_it->undo();
        }
    }
};

struct MoneyTransferCommand: CompositeBankAccountCommand {
    MoneyTransferCommand(BankAccount& from, BankAccount& to, int amount): CompositeBankAccountCommand({
        BankAccountCommand{from, BankAccountCommand::withdraw, amount},
        BankAccountCommand{to, BankAccountCommand::deposit, amount}
    }) {}
};
#endif