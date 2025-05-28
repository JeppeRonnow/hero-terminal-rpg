#include "EnemyFactory.hpp"

#include <cstdlib>
#include <ctime>
#include <vector>

Enemy EnemyFactory::generateEnemy(int heroLevel) {
    std::srand(std::time(nullptr)); // Seed the random number generator

    std::string adjective = getRandomAdjective(heroLevel);
    std::string type = getRandomType(heroLevel);
    std::string name = adjective + " " + type;

    int baseHP = 4; // Base HP
    int baseStrength = 1; // Base strength

    int hp = calculateHP(adjective, baseHP);
    int strength = calculateStrength(adjective, baseStrength);
    int xpReward = 100 + calculateXPReward(hp, strength);

    return Enemy(name, hp, strength, xpReward);
}

std::string EnemyFactory::getRandomAdjective(int heroLevel) {
    std:: vector<std::string> adjectives = {
        "Weak", "Frail", "Strong", "Stronger", "Elite"
    };

    // Adjust the range based on hero level
    int index = std::min(heroLevel, static_cast<int>(adjectives.size()) - 1);

    return adjectives[index];
}

std::string EnemyFactory::getRandomType(int heroLevel) {
    std::vector<std::string> types = {
        "Horse", "Goblin", "Monkey", "Unicorn", "Dragon"
    };

    // Adjust the range based on hero level
    int index = std::min(heroLevel, static_cast<int>(types.size()) - 1);

    return types[index];
}

int EnemyFactory::calculateHP(const std::string& adjective, int baseHP) {
    if (adjective == "Weak") {
        return baseHP;
    } else if (adjective == "Frail") {
        return baseHP + 3;
    } else if (adjective == "Strong") {
        return baseHP + 8;
    } else if (adjective == "Stronger") {
        return baseHP + 12;
    } else if (adjective == "Elite") {
        return baseHP + 25;
    }
    return baseHP; // Default case
}

int EnemyFactory::calculateStrength(const std::string& adjective, int baseStrength) {
    if (adjective == "Weak") {
        return baseStrength;
    } else if (adjective == "Frail") {
        return baseStrength + 1;
    } else if (adjective == "Strong") {
        return baseStrength + 2;
    } else if (adjective == "Stronger") {
        return baseStrength + 4;
    } else if (adjective == "Elite") {
        return baseStrength + 10;
    }
    return baseStrength; // Default case
}

int EnemyFactory::calculateXPReward(int hp, int strength) {
    return (hp * strength) * 2;
}