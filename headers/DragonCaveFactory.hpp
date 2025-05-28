#pragma once
#include "CaveFactory.hpp"
#include "EnemyFactory.hpp"

class DragonCaveFactory : public CaveFactory {
   public:
    Cave createCave(const Hero& hero) const override;
};
