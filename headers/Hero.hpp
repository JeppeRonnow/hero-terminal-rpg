#ifndef HERO_HPP
#define HERO_HPP

#include <string>
#include <iostream>

class Hero {
    public:
        Hero(std::string name, int xp = 0, int level = 1, int hp = 10, int strength = 2);
        
        void receiveDamage(int dmg);
        void gainXP(int amount);
        void levelUpIfReady();
    
        void printStats() const;

        bool isDead() const;
    
    private:
        std::string name;
        int xp;
        int level;
        int hp;
        int strength;
};

#endif