#include <iostream>

#include "../headers/Hero.hpp"

int main() {
    
    std::cout << "Jeppe's Terminal RPG" << std::endl;
    std::cout << "====================" << std::endl;

    // Create a hero
    Hero hero("Jeppe", 0, 1, 10, 2);
    hero.printStats();


    return 0;
}