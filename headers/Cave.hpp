#pragma once
#include <string>
#include <vector>

#include "Hero.hpp"
#include "Enemy.hpp"


class Cave{
public:
    Cave();
    ~Cave();
    Cave(std::string name, int goldReward);

    bool isCleaned() const;

    void clearEnemy(int index);

    void addEnemy(const Enemy& enemy);

    // Getters
    std::string getName();
    int getGoldReward();
    std::vector<Enemy> getEnemies();

private:
    std::string name;
    int goldReward;
    std::vector<Enemy> enemies;
};

