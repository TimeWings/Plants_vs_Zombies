#pragma once
#include "Zombie.h"
#include "Plants.h"
#include "PlantStatus.h"

class Zomboni : public Zombie
{
public:
	static Vector<Sprite*> IceSprite;
	Zomboni();
	Zomboni(Point position, int row, int col);
	void work();
	void Check_Attack();
	virtual void Attack(PlantStatus *plantstatus);
	virtual void Die(Node * pSender);
	virtual void Attacked();
	virtual void LostHead();
	virtual void Move();
	void ProductIce(Point position);
	bool Check_Ice(Sprite* sp);
	virtual void DamageZombie(int damage);
	virtual void DamageEquip(int damage);
	virtual void DamageBoth(int damage);
	virtual Sprite *MagnetEquip();
	void DamagePlant(PlantStatus *plantstatus);
	void Press(Plants * plant);
	void clearPlant(Node * pSender,Plants* plant);
	void clear(Node * pSender);
};
