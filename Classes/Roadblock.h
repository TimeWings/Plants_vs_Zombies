#pragma once
#include "ZombieEquipment.h"

class Roadblock : public ZombieEquipment 
{
public:
	Roadblock();
	virtual void Die();
	virtual void Damage(int damage);
	virtual void Move();
	virtual void Attack();
};