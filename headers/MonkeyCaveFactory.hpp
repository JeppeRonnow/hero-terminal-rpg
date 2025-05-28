#pragma once
#include "CaveFactory.hpp"
#include "EnemyFactory.hpp"

class MonkeyCaveFactory : public CaveFactory {
   public:
    Cave createCave(const Hero& hero) const override;
};
