#pragma once

#include <string>
#include <vector>


class Weapon {
public:
    Weapon();
    Weapon(const std::string& name, int baseDamage, int strengthModifier, int durability);

    ~Weapon();

    int calculateDamage(int Herostrength) const; // Calculate the damage dealt by the weapon combined with hero's strength
    void degrade(); // Decrease the durability of the weapon
    bool isBroken() const; // Check if the weapon is broken 

    // Getters
    std::string getName() const;
    int getDurability() const;

private:
    std::string name;
    int baseDamage;
    int strengthModifier;
    int durability;
};