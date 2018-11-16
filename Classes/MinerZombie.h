#pragma once
#include "BasicZombie.h"
#include "RoadblockZombie.h"

class MinerZombie : public RoadblockZombie
{
private:
	bool isDigging;
	bool onGround;
	float digSpeed;
public:
	MinerZombie(Point position, int row, int col);
	virtual void Attack_with_Equip(PlantStatus *plantstatus);
	virtual void Move_with_Equip();
	virtual void BasicMove();
	virtual void LostHead();
	void OutMud(Node* pSender);
};