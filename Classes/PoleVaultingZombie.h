#pragma once
#include "BasicZombie.h"
#include "Plants.h"
#include "PlantStatus.h"


class PoleVaultingZombie : public BasicZombie
{
private:
	bool hasPole=true;
public:
	PoleVaultingZombie(Point position, int row, int col);
	void work();
	void Check_Jump();
	void Jump();
	void afterJump(Node * pSender);
	void BasicDie(Node * pSender);
	virtual void LostHead();
	void BasicMove();
	void BasicAttack(PlantStatus *plantstatus);
};
