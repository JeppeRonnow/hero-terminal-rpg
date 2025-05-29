#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <iostream>
#include <string>

class Enemy {
    public:
        Enemy(std::string name, int hp, int strength, int xpReward);
    
        void receiveDamage(int dmg); // Reduce HP by damage amount
        
        void printStats() const; // Print enemy stats

        void printName() const; // Print enemy name

        bool isDead() const; // Check if the enemy is dead

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