#ifndef GAME_HPP
#define GAME_HPP

#include "Enemy.hpp"
#include "Hero.hpp"
#include "File_manager.hpp"
#include "EnemyFactory.hpp"
#include "Cave.hpp"
#include "HorseCaveFactory.hpp"
#include "DragonCaveFactory.hpp"
#include "UnicornCaveFactory.hpp"
#include "GoblinCaveFactory.hpp"
#include "MonkeyCaveFactory.hpp"
#include "Weapon.hpp"

#include <vector>
#include <memory> // for std::unique_ptr

class Game {
public:
    Game();

    // starts game
    void run();

private:

    // Menus
    void mainMenu();           // new or load game
    void adventureMenu();      // fight or save
    void fightMenu();          // choose enemy and fight
    void caveMenu();           // choose cave and fight
    void weaponMenu();        // choose weapon and equip

    // load functions
    void saveGame();           // save hero to file
    void loadGame();           // load hero from file

    // helper functions
    void displayEnemies() const;
    void displayCaves() const;

    // entities
    std::unique_ptr<Hero> currentHero;
    std::vector<Enemy> enemies;
    std::vector<Cave> caves;
    std::vector<Weapon> weapons;

    // fighting
    void updateWeapon();

    // game state
    bool isRunning = true;

    // caves
    void createCaves();
    void updateCaves(int caveIndex);

    void caveReward(int caveIndex, int goldReward);
};

#endif