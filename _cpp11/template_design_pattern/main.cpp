#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
#include <string>
using namespace std;

struct Creature
{
    int attack, health;

    Creature(int attack, int health) : attack(attack), health(health) {}
};

struct CardGame
{
    vector<Creature> creatures;

    CardGame(const vector<Creature> &creatures) : creatures(creatures) {}

    // return the index of the creature that won (is a live)
    // example:
    // - creature1 alive, creature2 dead, return creature1
    // - creature1 dead, creature2 alive, return creature2
    // - no clear winner: return -1
    int combat(int creature1, int creature2)
    {
        auto creat1 = creatures[creature1];
        auto creat2 = creatures[creature2];
        if(creat1.attack == creat2.attack && creat1.health == creat2.health) {
            return -1;
        } 
        while(creat2.health > 0 && !is_end()) {
                hit(creat1, creat2);
                if(creat2.health>0) {
                    auto tmp = creat1;
                    creat1 = creat2;
                    creat2 = tmp;
                    
                    int tmp_idx =  creature1;
                    creature1 = creature2;
                    creature2 = tmp_idx;
                }
        }

        if(creat2.health <=0) {
            return creature1;
        }
        
        return -1;
    }

    virtual void hit(Creature& attacker, Creature& other) = 0;
    virtual bool is_end() = 0;
};

struct TemporaryCardDamageGame : CardGame
{
    int current_round {0};
    int max_round{2};
    
    TemporaryCardDamageGame(const vector<Creature> &creatures) : CardGame(creatures) {}

    void hit(Creature &attacker, Creature &other) override {
        cout << "Temporary Game..    ";
        cout << "attacker: " << attacker.attack << "  health: " << attacker.health << endl;
        cout << "other: " << other.attack << "  health: " << other.health << endl;
        other.health -= attacker.attack;
        if(other.health > 0) {
            other.health += attacker.attack;
        }
        ++current_round;
    }
    bool is_end() override {
        return current_round >= max_round;
    }
};

struct PermanentCardDamageGame : CardGame
{
    PermanentCardDamageGame(const vector<Creature> &creatures) : CardGame(creatures) {}

    void hit(Creature &attacker, Creature &other) override
    {
      cout << " Permanent Game..    ";
      cout << "attacker: " << attacker.attack << "  health: " << attacker.health << endl;
      cout << "other: " << other.attack << "  health: " << other.health << endl;
      other.health -= attacker.attack;
    }

    bool is_end() override {
        return false;
    }
};

int main(int argc, char* argv[]) {
    PermanentCardDamageGame tcg{{
        {1, 2},
        {1, 3}
    }};
    int res = tcg.combat(0, 1);
    cout << "Player " << res << " win the game..." << endl;
    return 0;
}