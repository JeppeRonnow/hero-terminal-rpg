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

    bool isCleaned() const; // Check if the cave is completely cleaned

    void clearEnemy(int index); // Clear an enemy at a specific index

    void addEnemy(const Enemy& enemy); // Add an enemy to the cave

    // Getters
    std::string getName() const;
    int getGoldReward();
    std::vector<Enemy>& getEnemies();

    // display cave information
    void displayCaveInfo() const;

private:
    std::string name;
    int goldReward;
    std::vector<Enemy> enemies;
};

