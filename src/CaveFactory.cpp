#include "CaveFactory.hpp"

Cave CaveFactory::createHorseCave(const Hero& hero) {
    Cave cave("Horse Cave", 100);

    for (int i = 0; i < 5; ++i) {
        Enemy enemy = EnemyFactory::generateEnemy(hero.getLevel() + i, "Horse");
        cave.addEnemy(enemy);
    }

    return cave;
}

Cave CaveFactory::createGoblinCave(const Hero& hero) {
    Cave cave("Goblin Cave", 200);

    for (int i = 0; i < 5; ++i) {
        Enemy enemy = EnemyFactory::generateEnemy(hero.getLevel() + i, "Goblin");
        cave.addEnemy(enemy);
    }

    return cave;
}

Cave CaveFactory::createMonkeyCave(const Hero& hero) {
    Cave cave("Monkey Cave", 300);

    for (int i = 0; i < 5; ++i) {
        Enemy enemy = EnemyFactory::generateEnemy(hero.getLevel() + i, "Monkey");
        cave.addEnemy(enemy);
    }

    return cave;
}

Cave CaveFactory::createUnicornCave(const Hero& hero) {
    Cave cave("Unicorn Cave", 500);

    for (int i = 0; i < 5; ++i) {
        Enemy enemy = EnemyFactory::generateEnemy(hero.getLevel() + i, "Unicorn");
        cave.addEnemy(enemy);
    }

    return cave;
}

Cave CaveFactory::createDragonCave(const Hero& hero) {
    Cave cave("Dragon Cave", 1000);

    for (int i = 0; i < 5; ++i) {
        Enemy enemy = EnemyFactory::generateEnemy(hero.getLevel() + i, "Dragon");
        cave.addEnemy(enemy);
    }

    return cave;
}