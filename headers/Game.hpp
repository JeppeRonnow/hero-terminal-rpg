#ifndef GAME_HPP
#define GAME_HPP

#include "Enemy.hpp"
#include "Hero.hpp"
#include "File_manager.hpp"

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

    // load functions
    void saveGame();           // save hero to file
    void loadGame();           // load hero from file

    // helper functions
    void displayEnemies() const;

    // entities
    std::unique_ptr<Hero> currentHero;
    std::vector<Enemy> enemies;

    // game state
    bool isRunning = true;
};

#endif