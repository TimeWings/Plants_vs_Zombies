#pragma once
#include "Zombie.h"

class Gargantuar : public Zombie 
{
public:
	Gargantuar();
	Gargantuar(Point position, int row, int col);
	virtual void Attack(PlantStatus *plantstatus);
	virtual void BasicAttack(PlantStatus *plantstatus);
	void AfterAttack(Node * pSender);
	virtual void Move();
	virtual void BasicMove();
	void DamagePlant(Node * pSender, PlantStatus * plantstatus);
	void Press(Plants * plant);
	void clearPlant(Node * pSender, Plants * plant);
	virtual void LostHead();
	virtual void Attacked();
	virtual void Die(Node * pSender);
	virtual void DamageZombie(int damage);
	virtual void DamageEquip(int damage);
	virtual void DamageBoth(int damage);
	virtual Sprite *MagnetEquip();
};