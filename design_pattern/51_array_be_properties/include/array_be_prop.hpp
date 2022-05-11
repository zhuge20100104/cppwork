#ifndef _FREDRIC_ARRAY_BE_PEROPERTY_HPP_
#define _FREDRIC_ARRAY_BE_PEROPERTY_HPP_

#include <array>
#include <numeric>

class Creature {
    // count是array的大小，是个结束符
    enum Abilities {str, agl, intel, count};

    std::array<int, count> abilities;

public:
    int get_strength() {
        return abilities[str];
    }

    void set_strength(int val) {
        abilities[str] = val;
    }

    int get_agility() {
        return abilities[agl];
    }

    void set_agility(int val) {
        abilities[agl] = val;
    }

    int get_intelligence() {
        return abilities[intel];
    }

    void set_intelligence(int val) {
        abilities[intel] = val;
    }

    int sum() const {
        return std::accumulate(abilities.begin(), abilities.end(), 0);
    }

    double average() const {
        return sum()/(double)count;
    }

    int max() const {
        return *std::max_element(abilities.begin(), abilities.end());
    }
}; 

#endif