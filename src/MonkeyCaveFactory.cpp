#include "MonkeyCaveFactory.hpp"

Cave MonkeyCaveFactory::createCave(const Hero& hero) const {
    Cave cave("Monkey Cave", 300);

    for (int i = 0; i < 5; ++i) {
        Enemy enemy = EnemyFactory::generateEnemy(hero.getLevel() + i, "Monkey");
        cave.addEnemy(enemy);
    }

    return cave;
}
