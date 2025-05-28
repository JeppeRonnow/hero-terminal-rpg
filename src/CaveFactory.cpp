#include "CaveFactory.hpp"

Cave CaveFactory::createHorseCave(const Hero& hero) {
    Cave cave("Horse Cave", 100);

    for (int i = 0; i < 5; ++i) {
        Enemy enemy = EnemyFactory::generateEnemy(hero.getLevel(), "Horse");
        cave.addEnemy(enemy);
    }

    return cave;
}
