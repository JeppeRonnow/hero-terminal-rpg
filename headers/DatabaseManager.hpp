#pragma once

#define DATABASE_PATH "../gameDatabase.db"

#include <string>
#include <vector>
#include <iostream>
#include <sqlite3.h>

#include "Hero.hpp"
#include "Enemy.hpp"
#include "Weapon.hpp"

class DatabaseManager {
public:

    DatabaseManager(std::string databaseFilePath);

    // save
    void saveHero(const Hero& hero);
    void addWeaponToHero(const std::string& heroName, const Weapon& weapon);
    void logKill(const std::string& heroName, const std::string& weaponName);
    void saveHeroInventory(const Hero& hero);

    // load
    Hero loadHero(const std::string& heroName) const;
    std::vector<Weapon> loadHeroWeapons(const std::string& heroName) const;
    void loadHeroInventory(Hero& hero) const;

    // analytics
    void listHeroes() const;
    void monsterKillCount(const std::string& heroName) const;
    void monsterKillCountByWeapon(const std::string& heroName, const Weapon& weapon) const;
    void topHeroesByKills() const;

private:
    std::string databaseFilePath;  // Path to the database file
};