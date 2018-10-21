#pragma once
#include "Zombie.h"


class BasicZombie : public Zombie 
{
public:
	BasicZombie();
	BasicZombie(Point position);
	virtual bool isAttacking();
	virtual void attack();
	virtual void Die();
	void Self_Animation();
	virtual void Attacked();
	virtual void LostHand();
	virtual void LostHead();
	void clear(Node * pSender);
};