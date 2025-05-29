#include "EnemyFactory.hpp"

#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>

Enemy EnemyFactory::generateEnemy(int heroLevel, const std::string& type) {
    std::string adjective = getRandomAdjective(heroLevel);
    std::string name = adjective + " " + type;

    auto [baseHP, baseStrength] = getBaseStats(type); // Get base stats for the enemy type

    int hp = calculateHP(adjective, baseHP);
    int strength = calculateStrength(adjective, baseStrength);
    int xpReward = 100 + calculateXPReward(hp, strength); // Calculate XP reward based on HP and strength

    return Enemy(name, hp, strength, xpReward);
}

// Get base stats for different enemy types
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

// Generate a random adjective based on hero level
std::string EnemyFactory::getRandomAdjective(int heroLevel) {
    std::vector<std::string> adjectives = {
        "Weak", "Frail", "Strong", "Stronger", "Elite"
    };

    // Scale hero level to fit within the range of adjectives
    int scaledLevel = heroLevel / 2; // scale to adjust difficulty
    int index = std::min(scaledLevel, static_cast<int>(adjectives.size()) - 1);

    return adjectives[index];
}

// Calculate HP based on adjective and base HP
int EnemyFactory::calculateHP(const std::string& adjective, int baseHP) {
    static const std::map<std::string, int> hpMultipliers = {
        {"Weak", 1},
        {"Frail", 2},
        {"Strong", 4},
        {"Stronger", 6},
        {"Elite", 10}
    };

    auto it = hpMultipliers.find(adjective);
    if (it != hpMultipliers.end()) {
        return baseHP * it->second;
    }

    return baseHP; // Default case if adjective not found
}

// Calculate strength based on adjective and base strength
int EnemyFactory::calculateStrength(const std::string& adjective, int baseStrength) {
    static const std::map<std::string, int> strengthMultipliers = {
        {"Weak", 1},
        {"Frail", 2},
        {"Strong", 4},
        {"Stronger", 6},
        {"Elite", 10}
    };

    auto it = strengthMultipliers.find(adjective);
    if (it != strengthMultipliers.end()) {
        return baseStrength * it->second;
    }

    return baseStrength; // Default case if adjective not found
}

// Calculate XP reward based on HP and strength
int EnemyFactory::calculateXPReward(int hp, int strength) {
    return (hp * strength) * 2;
}