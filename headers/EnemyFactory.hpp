#pragma once

#include "Enemy.hpp"
#include <string>
#include <vector>

class EnemyFactory {
public:
    static Enemy generateEnemy(int heroLevel, const std::string& type);

private:

    static std::string getRandomAdjective(int heroLevel); // Generate a adjective based on hero level

    static std::pair<int, int> getBaseStats(const std::string& type); // Get base HP and strength for the given enemy type

    static int calculateHP(const std::string& adjective, int baseHP); // Calculate HP based on adjective and base HP
    static int calculateStrength(const std::string& adjective, int baseStrength); // Calculate strength based on adjective and base strength
    static int calculateXPReward(int hp, int strength); // Calculate XP reward based on HP and strength

};