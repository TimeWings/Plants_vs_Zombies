#pragma once
#include "ZombieEquipment.h"

class MinerCap : public ZombieEquipment
{
public:
	MinerCap();
	virtual void Damage(int damage);
};