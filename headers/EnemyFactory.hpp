#pragma once

#include "Enemy.hpp"
#include <string>
#include <vector>

class EnemyFactory {
public:
    static Enemy generateEnemy(int heroLevel);

private:
    static std::string getRandomAdjective(int heroLevel);
    static std::string getRandomType(int heroLevel);
    static int calculateHP(const std::string& adjective, int baseHP);
    static int calculateStrength(const std::string& adjective, int baseStrength);
    static int calculateXPReward(int hp, int strength);

};