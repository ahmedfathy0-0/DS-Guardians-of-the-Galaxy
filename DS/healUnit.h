#pragma once
#include "Unit.h"
class healUnit :
    public Unit
{
public:
    healUnit(int id, int jointime, double health, double power, int attackcapacity);
    void attack(Unit* target) override;
};

