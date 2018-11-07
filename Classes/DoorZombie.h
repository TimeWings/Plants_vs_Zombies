#pragma once
#include "BasicZombie.h"
#include "Door.h"

class DoorZombie : public BasicZombie
{
public:
	DoorZombie();
	DoorZombie(Point position, int row, int col);
	virtual void Attack(PlantStatus *plantstatus);
	void DoorAttack(PlantStatus *plantstatus);
	virtual void Move();
	void DoorMove();
	virtual void DamageBoth(int damage);
	virtual void DamageEquip(int damage);
	virtual void DamageZombie(int damage);
};