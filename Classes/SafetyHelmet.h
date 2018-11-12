#pragma once
#include "ZombieEquipment.h"

class SafetyHelmet : public ZombieEquipment
{
public:
	SafetyHelmet();
	virtual void Die();
	virtual void Damage(int damage);
	virtual void Move();
	virtual void Attack(double interval);
};
