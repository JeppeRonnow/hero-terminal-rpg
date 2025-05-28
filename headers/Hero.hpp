#ifndef HERO_HPP
#define HERO_HPP

#include <string>
#include <iostream>

class Hero {
    public:
        Hero(std::string name, int xp = 0, int level = 1, int hp = 10, int strength = 2, int gold = 0);
        
        void receiveDamage(int dmg);
        void gainXP(int amount);
        void levelUpIfReady();
    
        void printStats() const;

        bool isDead() const;

        // getter functions
        int getStrength() const { return strength; }
        std::string getName() const { return name; }
        int getHP() const { return hp; }
        int getXP() const { return xp; }
        int getLevel() const { return level; }
        int getGold() const { return gold; }

        //setter functions
        void setHP(int newHP) { hp = newHP; }

        
    
    private:
        std::string name;
        int xp;
        int level;
        int hp;
        int strength;
        int gold;
};

#endif