#ifndef _FREDRIC_LIST_CHAIN_HPP_
#define _FREDRIC_LIST_CHAIN_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <type_traits>
#include <typeinfo>

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
protected:
    Creature& creature;

public:
    CreatureModifer(Creature& creature_): creature{creature_} {}
    virtual void handle() = 0;
};


class DoubleAttackModifier: public CreatureModifer {
public:
    DoubleAttackModifier(Creature& creature_): CreatureModifer(creature_) {}

    void handle() override {
        creature.attack *= 2;
    }
};

class IncreaseDefenseModifer: public CreatureModifer {
public:
    IncreaseDefenseModifer(Creature& creature_): CreatureModifer(creature_) {}
    void handle() override {
        if(creature.attack <= 2) 
            ++ creature.defense;
    }
};

class NoBonusesModifier: public CreatureModifer {
public:
    NoBonusesModifier(Creature& creature_): CreatureModifer(creature_) {}
    // 啥都不干，断开链接
    void handle() override {
    }
};

struct CreatureModifierChain{
    std::vector<CreatureModifer*> modifiers{};

    void add(CreatureModifer* modifier) {
        modifiers.emplace_back(modifier);
    }

    void handle() {
        for(auto&& modifier: modifiers) {
            if(typeid(*modifier) == typeid(NoBonusesModifier)) {
                break;
            } else {
                modifier->handle();
            }
        }
    }
};

#endif