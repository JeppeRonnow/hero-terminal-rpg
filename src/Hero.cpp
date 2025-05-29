#include "../headers/Hero.hpp"

// constructor
Hero::Hero(std::string name, int xp, int level, int hp, int strength, int gold)
    : name(name), xp(xp), level(level), hp(hp), strength(strength), gold(gold) {}


// prints stats of the hero
void Hero::printStats() const {
    std::cout << name << " with " << hp << " hp, " << level << " level, " << gold << " gold, " << xp << " xp\n";
}

// is the hero dead?
bool Hero::isDead() const {
    return hp <= 0;
}

// receives damage
void Hero::receiveDamage(int dmg) {
    hp -= dmg;
    if (hp < 0) {
        hp = 0;
    }
}

// gain xp
void Hero::gainXP(int amount) {
    xp += amount;
}

// level up if ready (level * 1000)
void Hero::levelUpIfReady() {
    if (xp >= level * 1000) {
        xp -= level * 1000;
        level++;
        hp += 2;
        strength += 1; 
    }
}

void Hero::equipWeapon(const Weapon& weapon) {
    if (!weapon.isBroken()) {
        equippedWeapon = weapon;
        strength += weapon.calculateDamage(strength);
    } else {
        std::cout << "Weapon is broken and cannot be equipped.\n";
    }
}

void Hero::addWaponToInventory(const Weapon& weapon) {
    inventory.push_back(weapon);
}
