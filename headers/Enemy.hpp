#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <iostream>
#include <string>

class Enemy {
    public:
        Enemy(std::string name, int hp, int strength, int xpReward);
    
        void receiveDamage(int dmg);
        
        void printStats() const;

        bool isDead() const;
    
    private:
        std::string name;
        int hp;
        int strength;
        int xpReward;
};

#endif