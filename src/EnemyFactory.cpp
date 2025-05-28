#include "EnemyFactory.hpp"

#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>

Enemy EnemyFactory::generateEnemy(int heroLevel, const std::string& type) {
    std::string adjective = getRandomAdjective(heroLevel);
    std::string name = adjective + " " + type;

    auto [baseHP, baseStrength] = getBaseStats(type);

    int hp = calculateHP(adjective, baseHP);
    int strength = calculateStrength(adjective, baseStrength);
    int xpReward = 100 + calculateXPReward(hp, strength);

    return Enemy(name, hp, strength, xpReward);
}


std::pair<int, int> EnemyFactory::getBaseStats(const std::string& type) {
    static const std::map<std::string, std::pair<int, int>> baseStats = {
        {"Goblin", {4, 2}},  // {Base HP, Base Strength}
        {"Horse", {4, 1}},
        {"Monkey", {30, 5}},
        {"Unicorn", {5, 5}},
        {"Dragon", {100, 10}}};

    auto it = baseStats.find(type);
    if (it != baseStats.end()) {
        return it->second;
    }

    return {0, 0};  // Default case
}

std::string EnemyFactory::getRandomAdjective(int heroLevel) {
    std:: vector<std::string> adjectives = {
        "Weak", "Frail", "Strong", "Stronger", "Elite"
    };

    // Adjust the range based on hero level
    int index = std::min(heroLevel, static_cast<int>(adjectives.size()) - 1);

    return adjectives[index];
}


int EnemyFactory::calculateHP(const std::string& adjective, int baseHP) {
    static const std::map<std::string, int> hpMultipliers = {
        {"Weak", 1},
        {"Frail", 2},
        {"Strong", 3},
        {"Stronger", 5},
        {"Elite", 10}
    };

    auto it = hpMultipliers.find(adjective);
    if (it != hpMultipliers.end()) {
        return baseHP * it->second;
    }

    return baseHP; // Default case if adjective not found
}

int EnemyFactory::calculateStrength(const std::string& adjective, int baseStrength) {
    static const std::map<std::string, int> strengthMultipliers = {
        {"Weak", 1},
        {"Frail", 2},
        {"Strong", 3},
        {"Stronger", 5},
        {"Elite", 10}
    };

    auto it = strengthMultipliers.find(adjective);
    if (it != strengthMultipliers.end()) {
        return baseStrength * it->second;
    }

    return baseStrength; // Default case if adjective not found
}

int EnemyFactory::calculateXPReward(int hp, int strength) {
    return (hp * strength) * 2;
}