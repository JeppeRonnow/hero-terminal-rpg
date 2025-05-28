#include "Cave.hpp"

Cave::Cave(std::string name, int goldReward, std::vector<std::string> enemies)
    : name(name), goldReward(goldReward), enemies(enemies) {}

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

std::string Cave::getName() {
    return name;
}

int Cave::getGoldReward() {
    return goldReward;
}

std::vector<std::string> Cave::getEnemies() {
    return enemies;
}