#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <iostream>
#include <string>

class Enemy {
    public:
        Enemy(std::string name, int hp, int strength, int xpReward);
    
        void receiveDamage(int dmg);
        
        void printStats() const;

        void printName() const;

        bool isDead() const;

        // getter functions
        int getStrength() const { return strength; }
        std::string getName() const { return name; }
        int getXPReward() const { return xpReward; }
        int getHP() const { return hp; }
        
        // setter functions
        void setHP(int newHP) { hp = newHP; }

    private:
        std::string name;
        int hp;
        int strength;
        int xpReward;
};

#endif