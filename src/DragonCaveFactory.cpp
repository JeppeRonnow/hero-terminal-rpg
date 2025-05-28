#include "DragonCaveFactory.hpp"

Cave DragonCaveFactory::createCave(const Hero& hero) const {
    Cave cave("Dragon Cave", 1000);

    for (int i = 0; i < 5; ++i) {
        Enemy enemy = EnemyFactory::generateEnemy(hero.getLevel() + i, "Dragon");
        cave.addEnemy(enemy);
    }

    return cave;
}