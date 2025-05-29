#include "Weapon.hpp"

Weapon::Weapon() {};

Weapon::Weapon(const std::string& name, int baseDamage, int strengthModifier, int durability)
    : name(name), baseDamage(baseDamage), strengthModifier(strengthModifier), durability(durability) {}

Weapon::~Weapon() {}

// Calculate the damage dealt by the weapon combined with hero strength
int Weapon::calculateDamage(int Herostrength) const {
    return baseDamage + (strengthModifier * Herostrength);
}

// degrade the weapon's durability by 1
void Weapon::degrade() {
    if (durability > 0) {
        --durability;
    }
}

// Check if the weapon is broken
bool Weapon::isBroken() const {
    return durability <= 0;
}

std::string Weapon::getName() const {
    return name;
}

int Weapon::getDurability() const {
    return durability;
}