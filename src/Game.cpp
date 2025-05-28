#include "../headers/Game.hpp"

// constructor
Game::Game() {
    // Initialize enemies
    enemies.push_back(Enemy("Hest", 4, 1, 100));
    enemies.push_back(Enemy("Weak Goblin", 4, 2, 200));
    enemies.push_back(Enemy("Strong Goblin", 8, 3, 400));
    enemies.push_back(Enemy("Stronger Goblin", 10, 4, 500));
    enemies.push_back(Enemy("The Strongest Goblin", 15, 5, 800));
    enemies.push_back(Enemy("The Abe King", 30, 5, 1000));
    enemies.push_back(Enemy("Unicorn", 5, 8, 1500));
    enemies.push_back(Enemy("Dragon", 100, 10, 3000));
}

// run game
void Game::run() {
    std::cout << "     Crazy Terminal RPG\n";
    std::cout << "=============================\n";

    while (isRunning) {
        if (!currentHero)
            mainMenu();
        else
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

    // create caves
    createCaves();
}

void Game::createCaves() {
    CaveFactory caveFactory;

    std::cout << "Creating caves...\n";

    caves.push_back(caveFactory.createHorseCave(*currentHero));
}

// adventure menu
void Game::adventureMenu() {
    std::cout << "Your options are (0) Fight monster (1) Fight Caves (4) save and exit: ";
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 0:
            fightMenu();
            break;
        case 1:
            caveMenu();
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

// cave menu
void Game::caveMenu(){
    displayCaves();
    std::cout << "Select cave by index (-1 to exit): ";

    int caveIndex;
    std::cin >> caveIndex;
    
    // Exit the cave menu if the user enters -1
    if (caveIndex == -1) {
        return;
    }

    // check if the cave index is valid
    if (caveIndex < 0 || caveIndex >= caves.size()) {
        std::cout << "Invalid cave index. Try again.\n";
        return;
    }

    Cave& cave = caves[caveIndex];
    std::cout << "You entered " << cave.getName() << "\n";
    if (cave.isCleaned()) {
        std::cout << "This cave is already cleaned.\n";
        return;
    }

    std::cout << "You found " << cave.getEnemies().size() << " enemies in this cave.\n";

    while (!cave.isCleaned())    {
        cave.displayCaveInfo();
        std::cout << "Select enemy by index to fight: ";
        int enemyIndex;
        std::cin >> enemyIndex;
        enemyIndex -= 1;

        // check if the enemy index is valid
        if (enemyIndex < 0 || enemyIndex >= cave.getEnemies().size()) {
            std::cout << "Invalid enemy index. Try again.\n";
            return;
        }

        Enemy& enemy = cave.getEnemies()[enemyIndex];

        std::cout << "You are fighting " << enemy.getName() << "\n";

        // save start health
        int startHeroHP = currentHero->getHP();
        int startEnemyHP = enemy.getHP();

        while (!enemy.isDead() && !currentHero->isDead()) {
            enemy.printStats();
            currentHero->printStats();
            std::cout << "Press enter to fight";
            std::cin.ignore();
            std::cin.get();

            // Hero attacks enemy
            enemy.receiveDamage(currentHero->getStrength());

            // Enemy attacks hero
            if (!enemy.isDead()) {
                currentHero->receiveDamage(enemy.getStrength());
            } else {
                std::cout << enemy.getName() << " is defeated\n";
            }
        }

        // Check if hero is dead or enemy is dead
        if (enemy.isDead()) {
            currentHero->setHP(startHeroHP);  // restore health
            std::cout << "You won!\n";
            currentHero->gainXP(enemy.getXPReward());  // gain xp
            currentHero->levelUpIfReady();             // level up if ready
            currentHero->printStats();

            cave.clearEnemy(enemyIndex);  // clear enemy from cave
        } else {
            std::cout << "You were defeated by " << enemy.getName() << "\n";
            FileManager::deleteHero(currentHero->getName());  // delete hero if saved

            // delete current hero and go to main menu
            currentHero = nullptr;
        }

        enemy.setHP(startEnemyHP);  // restore health
    }
}

// fight menu
void Game::fightMenu() {
    displayEnemies();
    std::cout << "select enemy by index: ";

    int enemyIndex;
    std::cin >> enemyIndex;

    // check if the enemy index is valid
    if (enemyIndex < 0 || enemyIndex >= enemies.size()) {
        std::cout << "Invalid enemy index. Try again.\n";
        return;
    }

    Enemy& enemy = enemies[enemyIndex];

    // save start health
    int startHeroHP = currentHero->getHP();
    int startEnemyHP = enemy.getHP();

    while (!enemy.isDead() && !currentHero->isDead()) {
        enemy.printStats();
        currentHero->printStats();
        std::cout << "Press enter to fight";
        std::cin.ignore();
        std::cin.get();
        
        // Hero attacks enemy
        enemy.receiveDamage(currentHero->getStrength());

        // Enemy attacks hero
        if (!enemy.isDead()) {
            currentHero->receiveDamage(enemy.getStrength());
        }
        else {
            std::cout << enemy.getName() << " is defeated\n";
        }
    }


    // Check if hero is dead or enemy is dead
    if (enemy.isDead()) {
        currentHero->setHP(startHeroHP); // restore health
        std::cout << "You won!\n";
        currentHero->gainXP(enemy.getXPReward()); // gain xp
        currentHero->levelUpIfReady(); // level up if ready
        currentHero->printStats();
    } else {
        std::cout << "You were defeated by " << enemy.getName() << "\n";
        FileManager::deleteHero(currentHero->getName()); // delete hero if saved

        //delete current hero and go to main menu
        currentHero = nullptr;
    }

    enemy.setHP(startEnemyHP); // restore health
    
}

// displays all enemies
void Game::displayEnemies() const {
    for (size_t i = 0; i < enemies.size(); ++i) {
        std::cout << i << " : ";
        enemies[i].printName();
        
    }
}

void Game::displayCaves() const {
    for (size_t i = 0; i < caves.size(); ++i) {
        std::cout << i << " : " << caves[i].getName() << "\n";
    }
}

// saves current hero to file
void Game::saveGame() {
    FileManager::saveHero(*currentHero);
    std::cout << "Game saved\n";
}

// loads hero from file
void Game::loadGame() {
    std::string heroName;

    while (true) {
        std::cout << "Write name to load: ";
        std::cin >> heroName;

        try {
            currentHero = std::make_unique<Hero>(FileManager::loadHero(heroName));
            std::cout << "Game loaded\n";
            break;
        } catch (const std::runtime_error& e) {
            std::cout << e.what() << "\n";
        }
    }

    currentHero->printStats();
}