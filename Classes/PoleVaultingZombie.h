#pragma once
#include "BasicZombie.h"
#include "Plants.h"
#include "PlantStatus.h"


class PoleVaultingZombie : public BasicZombie
{
public:
	bool hasPole = true;
	PoleVaultingZombie(Point position, int row, int col);
	void Jump(bool canMove);
	void afterJump(Node * pSender);
	virtual void LostHead();
	void BasicMove();
	void BasicAttack(PlantStatus *plantstatus);
};
