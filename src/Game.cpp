#include "../headers/Game.hpp"

// constructor
Game::Game() {
    // Initialize enemies
    enemies.push_back(Enemy("Hest", 4, 1, 100));
    enemies.push_back(Enemy("Weak Goblin", 4, 2, 200));
}

// run game
void Game::run() {
    while (isRunning) {
        mainMenu();
        if (currentHero)
            adventureMenu();
    }
}

// main menu
void Game::mainMenu() {
    std::cout << "(0) New Game (1) Load Game: ";
    int choice;
    std::cin >> choice;

    std::string heroName;
    switch (choice) {
        case 0:
            std::cout << "Enter hero name: ";
            std::cin >> heroName;

            currentHero = std::make_unique<Hero>(heroName);
            break;
        case 1:
            loadGame();
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
            break;
    }
}

// adventure menu
void Game::adventureMenu() {
    std::cout << "Your options are (0) Fight monster (4) save and exit: ";
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 0:
            fightMenu();
            break;
        case 4:
            saveGame();
            isRunning = false;
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
            break;
    }
}

// fight menu
void Game::fightMenu() {
    displayEnemies();
    std::cout << "select enemy by index: ";

    int enemyIndex;
    std::cin >> enemyIndex;

    if (enemyIndex < 0 || enemyIndex >= enemies.size()) {
        std::cout << "Invalid enemy index. Try again.\n";
        return;
    }

    Enemy& enemy = enemies[enemyIndex];

    while (!enemy.isDead() && !currentHero->isDead()) {
        enemy.printStats();
    }

}

void Game::displayEnemies() const {
    for (size_t i = 0; i < enemies.size(); ++i) {
        std::cout << i << " : ";
        enemies[i].printName();
    }
}

void Game::saveGame() {
    std::cout << "Saving game...\n";
    // missing implementation
}

void Game::loadGame() {
    std::cout << "Loading game...\n";
    // missing implementation
}