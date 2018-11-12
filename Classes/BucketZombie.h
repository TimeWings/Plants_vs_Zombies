#pragma once
#include "RoadblockZombie.h"
#include "Bucket.h"

class BucketZombie : public RoadblockZombie 
{
public:
	BucketZombie();
	BucketZombie(Point position, int row, int col);
	virtual void Attack(PlantStatus *plantstatus);
	void Attack_with_Equip(PlantStatus *plantstatus);
	void Move_with_Equip();
	virtual void Move();
	virtual Sprite *MagnetEquip();
};