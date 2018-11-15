#pragma once
#include "BasicZombie.h"

class ImpZombie : public BasicZombie
{
public:
	ImpZombie();
	ImpZombie(Point position, int row, int col);
	virtual void Attack(PlantStatus *plantstatus);
	virtual void BasicAttack(PlantStatus *plantstatus);
	virtual void Move();
	virtual void BasicMove();
	virtual void LostHead();
};