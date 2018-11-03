#pragma once
#include "Zombie.h"
#include "Plants.h"


class BasicZombie : public Zombie 
{
public:
	BasicZombie();
	BasicZombie(Point position,int row,int col);
	virtual void Attack(Plants *plant);
	virtual void Die(Node * pSender);
	void BasicDie(Node * pSender);
	void Damage(Node * pSender, Plants* plant);
	virtual void Attacked();
	virtual void LostHead();
	virtual void Move();
	void BasicMove();
	void BasicAttack(Plants *plant);
	void clear(Node * pSender);
	void clear_from_vector(Node * pSender);
};