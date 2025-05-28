#pragma once
#include <string>
#include <vector>

#include "Cave.hpp"
#include "EnemyFactory.hpp"
#include "Hero.hpp"


class CaveFactory {
public:
    virtual ~CaveFactory() = default;

    virtual Cave createCave(const Hero& hero) const = 0;
private:

};