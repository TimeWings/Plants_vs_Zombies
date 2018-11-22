#pragma once
#include "ZombieEquipment.h"

class LadderEquip : public ZombieEquipment
{
public:
	LadderEquip();
	virtual void Die();
	virtual void Damage(int damage);
	virtual void Move();
	virtual void Attack(double interval);
	static Vector<Sprite*> LadderSprite;
};
