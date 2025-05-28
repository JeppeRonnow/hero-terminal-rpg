#include "GoblinCaveFactory.hpp"

Cave GoblinCaveFactory::createCave(const Hero& hero) const {
    Cave cave("Goblin Cave", 200);

    // Generate 5 goblin enemies based on the hero's level
    for (int i = 0; i < 5; ++i) {
        Enemy enemy = EnemyFactory::generateEnemy(hero.getLevel() + i, "Goblin");
        cave.addEnemy(enemy);
    }

    return cave;
}