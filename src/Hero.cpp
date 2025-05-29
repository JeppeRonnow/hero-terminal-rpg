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

int Hero::getFullStrength() const {
    return strength + weaponStrength;  // Add weapon damage
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

// equip a weapon from the inventory
void Hero::equipWeapon(const Weapon& weapon) {
    for (auto& invWeapon : inventory) {
        if (&invWeapon == &weapon && !weapon.isBroken()) { // Ensure weapon is in inventory and not broken
            equippedWeapon = &invWeapon; // Point to the weapon in the inventory
            weaponStrength = invWeapon.calculateDamage(strength); // Calculate weapon strength
            return;
        }
    }
    std::cout << "Weapon is either not in inventory or is broken.\n";
}

// unequip the currently equipped weapon
void Hero::unequipWeapon() {
    if (equippedWeapon) { // Check if a weapon is equipped
        weaponStrength = 0; // Reset weaponStrength to 0
        equippedWeapon = nullptr; // Reset the pointer
    } else {
        std::cout << "No weapon is currently equipped.\n";
    }
}

// add a weapon to the inventory
void Hero::addWeaponToInventory(const Weapon& weapon) {
    inventory.push_back(weapon);
}
