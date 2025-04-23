#include <iostream>

#include "../headers/Hero.hpp"
#include "../headers/Enemy.hpp"

int main() {
    
    std::cout << "Jeppe's Terminal RPG" << std::endl;
    std::cout << "====================" << std::endl;

    // Create a hero
    Hero hero("Jeppe");
    hero.printStats();

    // Create an enemy
    Enemy Hest("Hest", 4, 1, 100);
    Hest.printStats();

    return 0;
}