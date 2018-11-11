#pragma once
#include "BasicZombie.h"
#include "Door.h"

class DoorZombie : public BasicZombie
{
public:
	DoorZombie();
	DoorZombie(Point position, int row, int col);
	virtual void Attack(PlantStatus *plantstatus);
	void Attack_with_Equip(PlantStatus *plantstatus);
	virtual void Move();
	void Move_with_Equip();
	virtual void DamageBoth(int damage);
	virtual void DamageEquip(int damage);
	virtual void DamageZombie(int damage);
	virtual Sprite *MagnetEquip();
};