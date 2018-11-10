#pragma once
#include "BasicZombie.h"
#include "Roadblock.h"

class RoadblockZombie : public BasicZombie
{
public:
	RoadblockZombie();
	RoadblockZombie(Point position, int row, int col);
	virtual void Attack(PlantStatus *plantstatus);
	void Attack_with_Equip(PlantStatus *plantstatus);
	void Move_with_Equip();
	virtual void Move();
	virtual void DamageBoth(int damage);
	virtual void DamageEquip(int damage);
	virtual void DamageZombie(int damage);
};