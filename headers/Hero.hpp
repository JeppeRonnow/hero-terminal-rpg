#ifndef HERO_HPP
#define HERO_HPP

#include <string>
#include <iostream>
#include <vector>

#include "Weapon.hpp"

class Hero {
    public:
        Hero(std::string name, int xp = 0, int level = 1, int hp = 10, int strength = 2, int gold = 0);
        
        void receiveDamage(int dmg); // Reduce HP by damage amount
        void gainXP(int amount); // Gain experience points
        void levelUpIfReady(); // Check if the hero is ready to level up and do so if possible
    
        void printStats() const; // Print hero stats

        bool isDead() const; // Check if the hero is dead

        void equipWeapon(const Weapon& weapon); // Equip a weapon from the inventory
        void unequipWeapon(); // Remove the equipped weapon
        
        void addWeaponToInventory(const Weapon& weapon); // Add a weapon to the inventory

        // getter functions
        int getStrength() const { return strength; }
        int getFullStrength() const;
        std::string getName() const { return name; }
        int getHP() const { return hp; }
        int getXP() const { return xp; }
        int getLevel() const { return level; }
        int getGold() const { return gold; }
        Weapon* getWeapon() const { return equippedWeapon; } // Return pointer to equipped weapon
        const std::vector<Weapon>& getInventory() const { return inventory; }

        //setter functions
        void setHP(int newHP) { hp = newHP; }
        void setGold(int newGold) { gold = newGold; }
        
    
    private:
        std::string name;
        int xp;
        int level;
        int hp;
        int strength;
        int gold;
        int weaponStrength;  // Strength of equipped weapon

        std::vector<Weapon> inventory;
        Weapon* equippedWeapon = nullptr; // Pointer to a weapon in the inventory
};

#endif