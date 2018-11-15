#pragma once
#include "Zombie.h"
#include "Plants.h"
#include "PlantStatus.h"


class BasicZombie : public Zombie 
{
public:
	BasicZombie();
	BasicZombie(Point position,int row,int col);
	virtual void Attack(PlantStatus *plantstatus);
	virtual void BasicAttack(PlantStatus *plantstatus);
	virtual void Move();
	virtual void BasicMove();
	virtual void Die(Node * pSender);
	virtual void Attacked();
	virtual void LostHead();
	virtual void DamageZombie(int damage);
	virtual void DamageEquip(int damage);
	virtual void DamageBoth(int damage);
	virtual Sprite *MagnetEquip();
};