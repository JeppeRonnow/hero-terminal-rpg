#pragma once
#include <string>
#include <vector>

#include "Cave.hpp"
#include "EnemyFactory.hpp"
#include "Hero.hpp"


class CaveFactory {
public:
    static Cave createHorseCave(const Hero& hero);
    static Cave createGoblinCave(const Hero& hero);
    static Cave createMonkeyCave(const Hero& hero);
    static Cave createUnicornCave(const Hero& hero);
    static Cave createDragonCave(const Hero& hero);

private:

};