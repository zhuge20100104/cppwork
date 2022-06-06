#ifndef _FREDRIC_TEMPLATE_METHOD_HPP_
#define _FREDRIC_TEMPLATE_METHOD_HPP_

#include <iostream>
#include <string>
#include <vector>

class Game {
public:
    explicit Game(int number_of_players_): number_of_players {number_of_players_} {}

    void run() {
        start();
        while(!have_winner()) {
            take_turn();
        }
        std::cout << "Player " << get_winner() << " wins.\n";
    }

protected:
    virtual void start() = 0;
    virtual bool have_winner() = 0;
    virtual void take_turn() = 0;
    virtual int get_winner() = 0;

    int current_player {0};
    int number_of_players;
};

class Chess: public Game {
public:
    // 下象棋，两个人下
    explicit Chess(): Game{2} {}

protected:
    void start() override {
        std::cout << "Starting a game of chess with " << number_of_players << " players\n";
    }
    
    bool have_winner() override {
        return turns == max_turns;
    }

    void take_turn() override {
        std::cout << "Turn " << turns << " taken by player " << current_player << "\n";
        ++turns;
        current_player = (current_player + 1)% number_of_players;
        // For debugging popurse
        std::cout << "current_player: " << current_player << "\n";
    }   

    int get_winner() override {
        return current_player;
    }

private:
    int turns{0}, max_turns{10};
};

#endif