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
	void Damage(Node * pSender, PlantStatus *plantstatus);
	virtual void Attacked();
	virtual void LostHead();
	virtual void Move();
	void BasicMove();
	void BasicAttack(PlantStatus *plantstatus);
	void clear(Node * pSender);
	void clear_from_vector(Node * pSender);
	virtual void DamageZombie(int damage);
	virtual void DamageEquip(int damage);
	virtual void DamageBoth(int damage);
};