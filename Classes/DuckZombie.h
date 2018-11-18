#pragma once
#include "BasicZombie.h"
#include "Plants.h"
#include "PlantStatus.h"

class DuckZombie : public BasicZombie
{
public:
	DuckZombie(Point position, int row, int col);
	virtual void BasicAttack(PlantStatus *plantstatus);
	virtual void BasicMove();
	virtual void LostHead();
};