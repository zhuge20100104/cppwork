#ifndef _FREDRIC_POINTER_CHAIN_HPP_
#define _FREDRIC_POINTER_CHAIN_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

struct Creature {
    std::string name;
    int attack, defense;

    Creature(std::string const& name_, int attack_, int defense_): name{name_}, attack{attack_}, defense{defense_} {

    }

    friend std::ostream& operator<<(std::ostream& os, Creature const& c) {
        os << "name: " << c.name << " attack: " << c.attack << " defense: " << c.defense;
        return os;
    }
};

class CreatureModifer {
    CreatureModifer* next{nullptr};
protected:
    Creature& creature;

public:
    CreatureModifer(Creature& creature_): creature{creature_} {}
    // 构建单向链表
    void add(CreatureModifer* cm) {
        if(next) next->add(cm);
        else next = cm;
    }

    // 直接调用next的handle方法，接起链条
    virtual void handle() {
        if(next) next->handle();
    }
};


class DoubleAttackModifier: public CreatureModifer {
public:
    DoubleAttackModifier(Creature& creature_): CreatureModifer(creature_) {}

    void handle() override {
        creature.attack *= 2;
        CreatureModifer::handle();
    }
};

class IncreaseDefenseModifer: public CreatureModifer {
public:
    IncreaseDefenseModifer(Creature& creature_): CreatureModifer(creature_) {}
    void handle() override {
        if(creature.attack <= 2) 
            ++ creature.defense;
        CreatureModifer::handle();
    }
};

class NoBonusesModifier: public CreatureModifer {
public:
    NoBonusesModifier(Creature& creature_): CreatureModifer(creature_) {}
    // 啥都不干，断开链接
    void handle() override {
    }
};

#endif