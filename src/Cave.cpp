#include "Cave.hpp"

Cave::Cave(std::string name, int goldReward)
    : name(name), goldReward(goldReward) {}

Cave::~Cave() {}

// check if cave is empty of enemies
bool Cave::isCleaned() const{
    return enemies.empty();
}

// remove an enemy from the cave by index
void Cave::clearEnemy(int index) {
    if (index >= 0 && index < enemies.size()) {
        enemies.erase(enemies.begin() + index);
    }
}

void Cave::displayCaveInfo() const {
    std::cout << "Cave Name: " << name << "\n";
    std::cout << "Gold Reward: " << goldReward << "\n";
    std::cout << "Enemies in the cave:\n";
    for (size_t i = 0; i < enemies.size(); ++i) { // Loop through each enemy
        std::cout << i + 1 << ". ";
        enemies[i].printStats();
    }
}

// add an enemy to the cave
void Cave::addEnemy(const Enemy& enemy) {
    enemies.push_back(enemy);
}

std::string Cave::getName() const {
    return name;
}

int Cave::getGoldReward() {
    return goldReward;
}

std::vector<Enemy>& Cave::getEnemies() {
    return enemies;
}