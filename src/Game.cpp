#include "Game.hpp"

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

    // Initialize possible weapons
    weapons.push_back(Weapon("Stick", 0, 1, 7));
    weapons.push_back(Weapon("Metal Pipe", 0, 2, 20));
    weapons.push_back(Weapon("Knife", 5, 0, 20));
    weapons.push_back(Weapon("Sword", 20, 1, 30));
    weapons.push_back(Weapon("Morning Star", 10, 3, 40));
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
    caves.clear();  // Clear existing caves if you lose

    std::cout << "Creating caves...\n";

    HorseCaveFactory HorseCaveFactory;
    caves.push_back(HorseCaveFactory.createCave(*currentHero));
    GoblinCaveFactory GoblinCaveFactory;
    caves.push_back(GoblinCaveFactory.createCave(*currentHero));
    MonkeyCaveFactory MonkeyCaveFactory;
    caves.push_back(MonkeyCaveFactory.createCave(*currentHero));
    UnicornCaveFactory UnicornCaveFactory;
    caves.push_back(UnicornCaveFactory.createCave(*currentHero));
    DragonCaveFactory DragonCaveFactory;
    caves.push_back(DragonCaveFactory.createCave(*currentHero));
}

void Game::updateCaves(int caveIndex) {
    std::string caveName = caves[caveIndex].getName();
    std::cout << "Updating caves after clearing " << caveName << "\n";

    caves.erase(caves.begin() + caveIndex);  // Remove cleared cave

    if (caveName == "Horse Cave") {
        HorseCaveFactory HorseCaveFactory;
        caves.insert(caves.begin() + caveIndex, HorseCaveFactory.createCave(*currentHero));
    } else if (caveName == "Goblin Cave") {
        GoblinCaveFactory GoblinCaveFactory;
        caves.insert(caves.begin() + caveIndex, GoblinCaveFactory.createCave(*currentHero));
    } else if (caveName == "Monkey Cave") {
        MonkeyCaveFactory MonkeyCaveFactory;
        caves.insert(caves.begin() + caveIndex, MonkeyCaveFactory.createCave(*currentHero));
    } else if (caveName == "Unicorn Cave") {
        UnicornCaveFactory UnicornCaveFactory;
        caves.insert(caves.begin() + caveIndex, UnicornCaveFactory.createCave(*currentHero));
    } else if (caveName == "Dragon Cave") {
        DragonCaveFactory DragonCaveFactory;
        caves.insert(caves.begin() + caveIndex, DragonCaveFactory.createCave(*currentHero));
    }
}

// adventure menu
void Game::adventureMenu() {
    std::cout << "Your options are (0) Fight monster, (1) Fight Caves, (2) Weapon Inventory (4) save and exit: ";
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 0:
            fightMenu();
            break;
        case 1:
            caveMenu();
            break;
        case 2:
            weaponMenu();
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
            continue;
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
            updateWeapon();  // degrade weapon durability

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

            DatabaseManager db(DATABASE_PATH);

            std::string weaponName = "";
            if (currentHero->getWeapon() != nullptr) {
                weaponName = currentHero->getWeapon()->getName();
            }
            db.logKill(currentHero->getName(), weaponName);

            cave.clearEnemy(enemyIndex);  // clear enemy from cave
        } else {
            std::cout << "You were defeated by " << enemy.getName() << "\n";
            FileManager::deleteHero(currentHero->getName());  // delete hero if saved

            // delete current hero and go to main menu
            currentHero = nullptr;
            return;  // exit cave menu if hero is dead
        }

        enemy.setHP(startEnemyHP);  // restore health
    }

    updateCaves(caveIndex);  // update caves

    caveReward(caveIndex, cave.getGoldReward());  // give reward for clearing the cave

    
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

void Game::weaponMenu(){
    // if hero has no weapons in inventory
    if (currentHero->getInventory().empty()) {
        std::cout << "You have no weapons in your inventory.\n";
        return;
    }

    std::cout << "Your inventory:\n";

    const auto& inventory = currentHero->getInventory();
    for (size_t i = 0; i < inventory.size(); ++i) {
        std::cout << i + 1 << ": " << inventory[i].getName() << " (Durability: " << inventory[i].getDurability() << ")\n";
    }

    std::cout << "Select weapon to equip by index (-1 to exit): ";
    int choice;
    std::cin >> choice;

    if (choice == -1) {
        return; // Exit weapon menu
    }

    // Check if the choice is valid
    if (choice < 1 || choice > static_cast<int>(inventory.size())) {
        std::cout << "Invalid choice. Try again.\n";
        return;
    }

    // Equip the selected weapon
    currentHero->equipWeapon(inventory[choice - 1]);
    std::cout << "You equipped: " << currentHero->getWeapon()->getName() << "\n";
}

void Game::caveReward(int caveIndex, int goldReward) {
    // get gold reward for clearing the cave
    std::cout << "You cleared the cave and received " << goldReward << " gold!\n";
    currentHero->setGold(currentHero->getGold() + goldReward);  // add gold to hero

    // get weapon (based on index)
    std::cout << "You found a " << weapons[caveIndex].getName() << " in the cave!\n";
    std::cout << "remember to equip it in your inventory\n";

    // add weapon to hero's inventory
    currentHero->addWeaponToInventory(weapons[caveIndex]);

    currentHero->printStats();
}

void Game::updateWeapon() {
    // Check if a weapon is equipped
    Weapon* equippedWeapon = currentHero->getWeapon();
    if (equippedWeapon) {
        // Degrade weapon durability
        equippedWeapon->degrade();

        // Update weapon if it is broken
        if (equippedWeapon->isBroken()) {
            std::cout << "Your weapon is broken and cannot be used.\n";
            currentHero->unequipWeapon(); // Unequip broken weapon
        }
    }
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
    // save to database
    DatabaseManager db(DATABASE_PATH);
    db.saveHero(*currentHero);
    std::cout << "Hero saved to database\n";
}

// loads hero from file
void Game::loadGame() {
    std::string heroName;

    while (true) {
        std::cout << "Write name to load: ";
        std::cin >> heroName;

        try {
            DatabaseManager db(DATABASE_PATH);
            currentHero = std::make_unique<Hero>(db.loadHero(heroName));
            std::cout << "Loaded hero: " << currentHero->getName() << "\n";
            break;
        } catch (const std::exception& e) {
            std::cerr << "Fejl: " << e.what() << "\n";
        }
    }

    currentHero->printStats();
}