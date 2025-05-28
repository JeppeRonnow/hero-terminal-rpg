#pragma once
#include <string>
#include <vector>

#include "Hero.hpp"


class Cave{
public:
    Cave();
    ~Cave();
    Cave(std::string name, int goldReward, std::vector<std::string> enemies);

    bool isCleaned() const;

    void clearEnemy(int index);

    // Getters
    std::string getName();
    int getGoldReward();
    std::vector<std::string> getEnemies();

private:
    std::string name;
    int goldReward;
    std::vector<std::string> enemies;
};

