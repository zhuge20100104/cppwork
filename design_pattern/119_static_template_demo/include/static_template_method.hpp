#ifndef _FREDRIC_TEMPLATE_METHOD_HPP_
#define _FREDRIC_TEMPLATE_METHOD_HPP_

#include <iostream>
#include <string>
#include <vector>

template<typename T>
struct Game {
public:
    explicit Game(int number_of_players_): number_of_players {number_of_players_} {}

    void run() {
        T* game_type = static_cast<T*>(this);
        game_type->start();
        while(!game_type->have_winner()) {
            game_type->take_turn();
        }
        std::cout << "Player " << game_type->get_winner() << " wins.\n";
    }

    int current_player {0};
    int number_of_players;
};

struct Chess: public Game<Chess> {
public:
    // 下象棋，两个人下
    explicit Chess(): Game<Chess>{2} {}

public:
    void start()  {
        std::cout << "Starting a game of chess with " << number_of_players << " players\n";
    }
    
    bool have_winner() {
        return turns == max_turns;
    }

    void take_turn() {
        std::cout << "Turn " << turns << " taken by player " << current_player << "\n";
        ++turns;
        current_player = (current_player + 1)% number_of_players;
        // For debugging popurse
        std::cout << "current_player: " << current_player << "\n";
    }   

    int get_winner() {
        return current_player;
    }

private:
    int turns{0}, max_turns{10};
};

#endif