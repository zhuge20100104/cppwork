#ifndef _FREDRIC_BROKEN_CHAIN_HPP_
#define _FREDRIC_BROKEN_CHAIN_HPP_

#include <boost/signals2.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

struct Query {
    std::string creature_name;
    enum Argument {attack, defense} argument;
    int result;

    Query(std::string const& creature_name_, Argument argument_, int result_): argument{argument_}, result{result_}, creature_name{creature_name_}  {}
};

// mediator
struct Game {
    boost::signals2::signal<void(Query&)> queries;
};

struct Creature {
    Game& game;
    int attack, defense;
    std::string name;
public:
    Creature(Game& game_, int attack_, int defense_, std::string const& name_): game{game_}, attack{attack_}, defense{defense_}, name{name_} {}

    int get_attack() const {
        Query q {name, Query::Argument::attack, attack};
        game.queries(q);
        return q.result;
    }

    int get_defense() const {
        Query q {name, Query::Argument::defense, defense};
        game.queries(q);
        return q.result;
    }

    friend std::ostream& operator<<(std::ostream& os, Creature const& c) {
        os << "attack: " << c.get_attack() << " defense: " << c.get_defense() << " name: " << c.name;
        return os;
    }
};

class CreatureModifier {
protected:
    Game& game;
    Creature& creature;
public:
    CreatureModifier(Game& game_, Creature& creature_): game{game_}, creature{creature_} {

    }

    virtual ~CreatureModifier() = default;
};

class DoubleAttackModifier: public CreatureModifier {
    boost::signals2::connection conn;
public:
    DoubleAttackModifier(Game& game_, Creature& creature_): CreatureModifier(game_, creature_){
        conn = game.queries.connect([&](Query& q){
            if(q.creature_name == creature.name && q.argument == Query::Argument::attack) {
                q.result *= 2;
            }
        });
    }
};


class IncreaseDefenseModifier: public CreatureModifier {
    boost::signals2::connection conn;
    int attack{0};
public:
    IncreaseDefenseModifier(Game& game_, Creature& creature_): CreatureModifier(game_, creature_){
        attack = creature.get_attack();
        conn = game.queries.connect([&](Query& q){
            if(attack <= 2) {
                if(q.creature_name == creature.name && q.argument == Query::Argument::defense) {
                    q.result += 1; 
                }
            }
        });
    }
};

#endif