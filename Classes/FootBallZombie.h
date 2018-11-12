#pragma once
#include "RoadblockZombie.h"
#include "Roadblock.h"
#include "PlantStatus.h"
#include "SafetyHelmet.h"
class FootBallZombie : public RoadblockZombie
{
public:
	FootBallZombie(Point position, int row, int col);
	void BasicAttack(PlantStatus *plantstatus);
	void Attack_with_Equip(PlantStatus *plantstatus);
	void Lost_Equip();
	void Lost_Equip_Animation();
	void Move_with_Equip();
	void BasicMove();
	void LostHead();
};
