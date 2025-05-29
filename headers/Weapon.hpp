#pragma once

#include <string>
#include <vector>


class Weapon {
public:
    Weapon();
    Weapon(const std::string& name, int baseDamage, int strengthModifier, int durability);

    ~Weapon();

    int calculateDamage(int Herostrength) const;
    void degrade();
    bool isBroken() const;

    std::string getName() const;
    int getDurability() const;

private:
    std::string name;
    int baseDamage;
    int strengthModifier;
    int durability;
};