#include "UnicornCaveFactory.hpp"

Cave UnicornCaveFactory::createCave(const Hero& hero) const {
    Cave cave("Unicorn Cave", 500);

    for (int i = 0; i < 5; ++i) {
        Enemy enemy = EnemyFactory::generateEnemy(hero.getLevel() + i, "Unicorn");
        cave.addEnemy(enemy);
    }

    return cave;
}
