#pragma once
#include "Zombie.h"
#include "Plants.h"


class BasicZombie : public Zombie 
{
public:
	BasicZombie();
	BasicZombie(Point position,int row,int col);
	virtual bool isAttacking();
	virtual void attack(Plants *plant);
	virtual void Die(Node * pSender);
	void Self_Animation();
	void Damage(Node * pSender, Plants* plant);
	virtual void Attacked();
	virtual void LostHead();
	virtual void Move();
	void clear(Node * pSender);
	void clearhead(Node * pSender);
};