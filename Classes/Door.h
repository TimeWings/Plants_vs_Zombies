#pragma once
#include "ZombieEquipment.h"

class Door : public ZombieEquipment {
public:
	Door();
	virtual void Die();
	virtual void Damage(int damage);
	virtual void Move();
	void DoorMove();
	virtual void Attack();
	void DoorAttack();
};