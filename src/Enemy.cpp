# include "../headers/Enemy.hpp"

// constructor
Enemy::Enemy(std::string name, int hp, int strength, int xpReward)
    : name(name), hp(hp), strength(strength), xpReward(xpReward) {}

// prints stats of the enemy
void Enemy::printStats() const {
    std::cout << name << " with " << hp << " remaining life\n";
}

// prints name of the enemy
void Enemy::printName() const {
    std::cout << name << "\n";
}

// is the enemy dead?
bool Enemy::isDead() const {
    return hp <= 0;
}

// receives damage
void Enemy::receiveDamage(int dmg) {
    hp -= dmg;
    if (hp < 0) {
        hp = 0;
    }
}

