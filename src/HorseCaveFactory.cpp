#include "HorseCaveFactory.hpp"

Cave HorseCaveFactory::createCave(const Hero& hero) const {
    Cave cave("Horse Cave", 100);

    // Generate 5 goblin enemies based on the hero's level
    for (int i = 0; i < 5; ++i) {
        Enemy enemy = EnemyFactory::generateEnemy(hero.getLevel() + i, "Horse");
        cave.addEnemy(enemy);
    }

    return cave;
}