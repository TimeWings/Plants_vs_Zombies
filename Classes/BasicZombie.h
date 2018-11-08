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
	virtual void Die(Node * pSender);
	void BasicDie(Node * pSender);
	virtual void Attacked();
	virtual void LostHead();
	virtual void Move();
	void BasicMove();
	void BasicAttack(PlantStatus *plantstatus);
	virtual void DamageZombie(int damage);
	virtual void DamageEquip(int damage);
	virtual void DamageBoth(int damage);
	virtual Sprite *MagnetEquip();
};