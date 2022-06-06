#ifndef _FREDRIC_SOCCER_HPP_
#define _FREDRIC_SOCCER_HPP_

#include <boost/signals2.hpp>
#include <iostream>

namespace sig = boost::signals2;

struct EventData {
    virtual ~EventData() = default;
    virtual void print() const = 0;
};

struct PlayerScoredData: EventData {
    std::string player_name;
    int goals_scored_so_far;

    PlayerScoredData(std::string const& player_name_, int const goals_scored_so_far_): player_name{player_name_}, goals_scored_so_far{goals_scored_so_far_} {

    }

    void print() const override {
        std::cout << player_name << " has scored! (their "  <<
            goals_scored_so_far << " goal)" << "\n";
    }
};

// 观察者
struct Game {
    sig::signal<void(EventData*)> events;
};

struct Player {
    std::string name;
    int goals_scored{0};
    Game& game;

    Player(std::string const& name_, Game& game_): name{name_}, game{game_} {

    }

    void score() {
        ++ goals_scored;
        PlayerScoredData ps {name, goals_scored};
        // Send events once scored
        game.events(&ps);
    }
};

struct Coach {
    Game& game;
    explicit Coach(Game& game_): game{game_} {
        // Celebrate if player has scored < 3 goals
        game.events.connect([](EventData* e){
            PlayerScoredData* ps = dynamic_cast<PlayerScoredData*>(e);
            ps->print();
            if(ps && ps->goals_scored_so_far < 3) {
                std::cout << "coach says: well done, " << ps->player_name << "\n";
            }
        });
    }
};
#endif